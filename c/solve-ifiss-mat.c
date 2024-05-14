static char help[] = "(Attempts to) apply the 2023 preconditioner of Benzi and Faccio\n\n";

#include <petscmat.h>
#include <petscviewer.h>
#include <petscvec.h>
#include <petscis.h>
#include <petscksp.h>
#include <string>
#include <iostream>
#include <cassert>

#ifdef HAVE_GPERFTOOLS
#include "gperftools/profiler.h"
#endif

PetscErrorCode
create_identity(PetscInt m, Mat & identity)
{
  PetscInt start, stop;
  PetscFunctionBegin;
  PetscCall(MatCreate(PETSC_COMM_WORLD, &identity));
  PetscCall(MatSetType(identity, MATMPIAIJ));
  PetscCall(MatSetSizes(identity, m, m, PETSC_DETERMINE, PETSC_DETERMINE));
  PetscCall(MatGetOwnershipRange(identity, &start, &stop));
  static constexpr PetscScalar one = 1;
  for (PetscInt i = start; i < stop; ++i)
    PetscCall(MatSetValues(identity, 1, &i, 1, &i, &one, INSERT_VALUES));
  PetscCall(MatAssemblyBegin(identity, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(identity, MAT_FINAL_ASSEMBLY));
  PetscFunctionReturn(PETSC_SUCCESS);
}

struct SMWPC
{
  Mat U, UT, D, aD, aDinv, Ik, I_plus_gammaUTaDinvU;
  PC smw_cholesky;
  PetscReal gamma, alpha;
  bool setup_called;

  SMWPC(Mat U_in, Mat D_in, PetscReal gamma_in, PetscReal alpha_in)
    : U(U_in),
      UT(nullptr),
      D(D_in),
      aD(nullptr),
      aDinv(nullptr),
      Ik(nullptr),
      I_plus_gammaUTaDinvU(nullptr),
      smw_cholesky(nullptr),
      gamma(gamma_in),
      alpha(alpha_in),
      setup_called(false)
  {
  }

  PetscErrorCode destroy()
  {
    PetscFunctionBegin;

    PetscCall(MatDestroy(&UT));
    PetscCall(MatDestroy(&Ik));
    PetscCall(MatDestroy(&I_plus_gammaUTaDinvU));
    PetscCall(MatDestroy(&aD));
    PetscCall(MatDestroy(&aDinv));
    PetscCall(PCDestroy(&smw_cholesky));

    PetscFunctionReturn(PETSC_SUCCESS);
  }

  PetscErrorCode setup()
  {
    PetscInt k;

    PetscFunctionBegin;

    if (setup_called)
      PetscFunctionReturn(PETSC_SUCCESS);

    // Create aD
    PetscCall(MatDuplicate(D, MAT_COPY_VALUES, &aD));
    PetscCall(MatScale(aD, alpha));

    // Create aDinv
    PetscCall(MatDuplicate(aD, MAT_DO_NOT_COPY_VALUES, &aDinv));
    {
      Vec aDVec;
      PetscCall(MatCreateVecs(aD, &aDVec, nullptr));
      PetscCall(MatGetDiagonal(aD, aDVec));
      PetscCall(VecReciprocal(aDVec));
      PetscCall(MatDiagonalSet(aDinv, aDVec, INSERT_VALUES));
      PetscCall(VecDestroy(&aDVec));
    }

    // Create UT
    PetscCall(MatTranspose(U, MAT_INITIAL_MATRIX, &UT));

    // Create Ik
    PetscCall(MatGetLocalSize(U, nullptr, &k));
    PetscCall(create_identity(k, Ik));

    // Create sum Mat
    PetscCall(
        MatMatMatMult(UT, aDinv, U, MAT_INITIAL_MATRIX, PETSC_DEFAULT, &I_plus_gammaUTaDinvU));
    PetscCall(MatScale(I_plus_gammaUTaDinvU, gamma));
    PetscCall(MatAXPY(I_plus_gammaUTaDinvU, 1., Ik, SUBSET_NONZERO_PATTERN));

    PetscCall(PCCreate(PETSC_COMM_WORLD, &smw_cholesky));
    PetscCall(PCSetType(smw_cholesky, PCCHOLESKY));
    PetscCall(PCSetOperators(smw_cholesky, I_plus_gammaUTaDinvU, I_plus_gammaUTaDinvU));
    PetscCall(PCSetOptionsPrefix(smw_cholesky, "smw_"));
    PetscCall(PCSetFromOptions(smw_cholesky));
    PetscCall(PCSetUp(smw_cholesky));

    setup_called = true;

    PetscFunctionReturn(PETSC_SUCCESS);
  }

  PetscErrorCode apply(Vec x, Vec y)
  {
    Vec vel0, pressure0, pressure1;
    PetscFunctionBegin;
    PetscCall(MatCreateVecs(UT, &vel0, &pressure0));
    PetscCall(VecDuplicate(pressure0, &pressure1));

    // First term
    PetscCall(MatMult(aDinv, x, vel0));
    PetscCall(MatMult(UT, vel0, pressure0));
    PetscCall(PCApply(smw_cholesky, pressure0, pressure1));
    PetscCall(MatMult(U, pressure1, vel0));
    PetscCall(MatMult(aDinv, vel0, y));
    PetscCall(VecScale(y, -gamma));

    // Second term
    PetscCall(MatMult(aDinv, x, vel0));

    PetscCall(VecAXPY(y, 1, vel0));

    PetscCall(VecDestroy(&vel0));
    PetscCall(VecDestroy(&pressure0));
    PetscCall(VecDestroy(&pressure1));
    PetscFunctionReturn(PETSC_SUCCESS);
  }
};

PetscErrorCode
smw_setup(PC pc)
{
  SMWPC * ctx;

  PetscFunctionBegin;
  PetscCall(PCShellGetContext(pc, &ctx));
  PetscCall(ctx->setup());
  PetscFunctionReturn(PETSC_SUCCESS);
}

PetscErrorCode
smw_apply(PC pc, Vec x, Vec y)
{
  SMWPC * ctx;

  PetscFunctionBegin;
  PetscCall(PCShellGetContext(pc, &ctx));
  PetscCall(ctx->apply(x, y));
  PetscFunctionReturn(PETSC_SUCCESS);
}

int
main(int argc, char ** args)
{
  Mat A, B, Q, Acondensed, Bcondensed, BT, J, AplusJ, QInv, D, AplusD, JplusD, U;
  Vec bound, x, b, Qdiag, DVec;
  PetscBool flg;
  PetscViewer viewer;
  char file[PETSC_MAX_PATH_LEN];
  PetscInt * boundary_indices;
  PetscInt boundary_indices_size, am, an, bm, bn, condensed_am, maxits, astart, aend, Dstart, Dend;
  PetscScalar * boundary_indices_values;
  IS boundary_is, bulk_is;
  KSP ksp;
  PC pc, pcA, pcJ;
  PetscRandom rctx;
  PetscScalar gamma = 100;
  PetscScalar alpha = .01;
  PetscReal dtol;
  PetscMPIInt rank;

  PetscFunctionBeginUser;
  PetscCall(PetscInitialize(&argc, &args, (char *)0, help));
  PetscCallMPI(MPI_Comm_rank(PETSC_COMM_WORLD, &rank));

#ifdef HAVE_GPERFTOOLS
  bool has_cpu_profiling = false;
  static std::string cpu_profile_file;

  if (std::getenv("PROFILE_BASE"))
  {
    has_cpu_profiling = true;
    cpu_profile_file = std::getenv("PROFILE_BASE") + std::to_string(rank) + ".prof";
  }

  if (has_cpu_profiling)
  {
    const auto success = ProfilerStart(cpu_profile_file.c_str());
    assert(success);
  }
#endif

  auto create_and_load_mat = [&flg, &viewer, &file](const std::string & mat_name, Mat & mat)
  {
    PetscFunctionBeginUser;

    PetscCall(PetscOptionsGetString(
        nullptr, nullptr, std::string("-f" + mat_name).c_str(), file, sizeof(file), &flg));
    PetscCheck(
        flg, PETSC_COMM_WORLD, PETSC_ERR_USER, "Must indicate file with the -f<mat_name> option");
    PetscCall(PetscViewerBinaryOpen(PETSC_COMM_WORLD, file, FILE_MODE_READ, &viewer));
    PetscCall(MatCreate(PETSC_COMM_WORLD, &mat));
    PetscCall(MatSetType(mat, MATMPIAIJ));
    PetscCall(PetscObjectSetName((PetscObject)mat, mat_name.c_str()));
    PetscCall(MatSetFromOptions(mat));
    PetscCall(MatLoad(mat, viewer));
    PetscCall(PetscViewerDestroy(&viewer));
    PetscFunctionReturn(PETSC_SUCCESS);
  };

  create_and_load_mat("Anst", A);
  create_and_load_mat("Bst", B);
  create_and_load_mat("Q", Q);

  PetscCall(PetscOptionsGetString(nullptr, nullptr, "-fbound", file, sizeof(file), &flg));
  PetscCheck(flg, PETSC_COMM_WORLD, PETSC_ERR_USER, "Must indicate file with the -fbound option");

  if (rank == 0)
  {
    PetscCall(PetscViewerBinaryOpen(PETSC_COMM_SELF, file, FILE_MODE_READ, &viewer));
    PetscCall(VecCreate(PETSC_COMM_SELF, &bound));
    PetscCall(PetscObjectSetName((PetscObject)bound, "bound"));
    PetscCall(VecSetType(bound, VECSEQ));
    PetscCall(VecLoad(bound, viewer));
    PetscCall(PetscViewerDestroy(&viewer));
    PetscCall(VecGetLocalSize(bound, &boundary_indices_size));
    PetscCall(VecGetArray(bound, &boundary_indices_values));
  }
  PetscCallMPI(MPI_Bcast(&boundary_indices_size, 1, MPIU_INT, 0, PETSC_COMM_WORLD));
  if (rank != 0)
    PetscCall(PetscMalloc1(boundary_indices_size, &boundary_indices_values));
  PetscCallMPI(
      MPI_Bcast(boundary_indices_values, boundary_indices_size, MPIU_SCALAR, 0, PETSC_COMM_WORLD));

  PetscCall(MatGetSize(A, &am, nullptr));
  // The total number of dofs for a given velocity component
  assert((am % 2) == 0);
  const auto nc = am / 2;
  PetscCall(MatGetOwnershipRange(A, &astart, &aend));

  PetscInt num_local_bnd_dofs = 0;
  PetscCall(PetscMalloc1(2 * boundary_indices_size, &boundary_indices));

  //
  // The dof index ordering appears to be all vx dofs and then all vy dofs.
  //

  // First do vx
  for (PetscInt i = 0; i < boundary_indices_size; ++i)
  {
    // Matlab uses 1-based indexing
    const PetscInt bnd_dof = (PetscInt)boundary_indices_values[i] - 1;
    if ((bnd_dof >= astart) && (bnd_dof < aend))
      boundary_indices[num_local_bnd_dofs++] = bnd_dof;
  }

  // Now vy
  for (PetscInt i = 0; i < boundary_indices_size; ++i)
  {
    // Matlab uses 1-based indexing
    const PetscInt bnd_dof = ((PetscInt)boundary_indices_values[i] - 1) + nc;
    if ((bnd_dof >= astart) && (bnd_dof < aend))
      boundary_indices[num_local_bnd_dofs++] = bnd_dof;
  }
  if (rank == 0)
    PetscCall(VecRestoreArray(bound, &boundary_indices_values));
  else
    PetscCall(PetscFree(boundary_indices_values));

  PetscCall(ISCreateGeneral(
      PETSC_COMM_WORLD, num_local_bnd_dofs, boundary_indices, PETSC_USE_POINTER, &boundary_is));
  PetscCall(ISComplement(boundary_is, astart, aend, &bulk_is));

  PetscCall(MatCreateSubMatrix(A, bulk_is, bulk_is, MAT_INITIAL_MATRIX, &Acondensed));
  // Can't pass null for row index set :-(
  PetscCall(MatTranspose(B, MAT_INPLACE_MATRIX, &B));
  PetscCall(MatCreateSubMatrix(B, bulk_is, nullptr, MAT_INITIAL_MATRIX, &Bcondensed));
  PetscCall(MatGetLocalSize(Acondensed, &am, &an));
  PetscCall(MatGetLocalSize(Bcondensed, &bm, &bn));
  assert(am == an);
  assert(am == bm);

  // Create QInv
  PetscCall(MatCreateVecs(Q, &Qdiag, nullptr));
  PetscCall(MatGetDiagonal(Q, Qdiag));
  PetscCall(VecReciprocal(Qdiag));
  PetscCall(MatDuplicate(Q, MAT_DO_NOT_COPY_VALUES, &QInv));
  PetscCall(MatDiagonalSet(QInv, Qdiag, INSERT_VALUES));
  PetscCall(MatAssemblyBegin(QInv, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(QInv, MAT_FINAL_ASSEMBLY));

  // Create J
  PetscCall(MatTranspose(Bcondensed, MAT_INITIAL_MATRIX, &BT));
  PetscCall(MatMatMatMult(Bcondensed, QInv, BT, MAT_INITIAL_MATRIX, PETSC_DEFAULT, &J));
  PetscCall(MatScale(J, gamma));

  // Create sum of A + J
  PetscCall(MatDuplicate(Acondensed, MAT_COPY_VALUES, &AplusJ));
  PetscCall(MatAXPY(AplusJ, 1.0, J, DIFFERENT_NONZERO_PATTERN));

  // Create decomposition matrices
  // We've already used Qdiag, which currently represents Q^-1,  for it's necessary purposes. Let's
  // convert it to represent Q^(-1/2)
  PetscCall(VecSqrtAbs(Qdiag));
  // We can similarly reuse Qinv
  PetscCall(MatDiagonalSet(QInv, Qdiag, INSERT_VALUES));
  PetscCall(MatAssemblyBegin(QInv, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(QInv, MAT_FINAL_ASSEMBLY));
  // Create U
  PetscCall(MatMatMult(Bcondensed, QInv, MAT_INITIAL_MATRIX, PETSC_DEFAULT, &U));

  // Create x and b
  PetscCall(MatCreateVecs(AplusJ, &x, &b));
  PetscCall(PetscRandomCreate(PETSC_COMM_WORLD, &rctx));
  PetscCall(VecSetRandom(x, rctx));
  PetscCall(PetscRandomDestroy(&rctx));
  PetscCall(MatMult(AplusJ, x, b));

  // Compute preconditioner operators
  PetscCall(MatGetLocalSize(Acondensed, &condensed_am, nullptr));
  PetscCall(MatCreate(PETSC_COMM_WORLD, &D));
  PetscCall(MatSetType(D, MATMPIAIJ));
  PetscCall(MatSetSizes(D, condensed_am, condensed_am, PETSC_DETERMINE, PETSC_DETERMINE));
  PetscCall(MatGetOwnershipRange(D, &Dstart, &Dend));
  static constexpr PetscScalar zero = 0;
  for (PetscInt i = Dstart; i < Dend; ++i)
    PetscCall(MatSetValues(D, 1, &i, 1, &i, &zero, INSERT_VALUES));
  PetscCall(MatAssemblyBegin(D, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(D, MAT_FINAL_ASSEMBLY));
  PetscCall(MatCreateVecs(D, &DVec, nullptr));
  PetscCall(MatGetDiagonal(AplusJ, DVec));
  PetscCall(MatDiagonalSet(D, DVec, INSERT_VALUES));
  PetscCall(MatDuplicate(Acondensed, MAT_COPY_VALUES, &AplusD));
  PetscCall(MatAXPY(AplusD, alpha, D, SUBSET_NONZERO_PATTERN));
  PetscCall(MatDuplicate(J, MAT_COPY_VALUES, &JplusD));
  PetscCall(MatAXPY(JplusD, alpha, D, SUBSET_NONZERO_PATTERN));

  // Create our SMW context
  SMWPC test_pc(U, D, gamma, alpha);

  // Set preconditioner operators
  PetscCall(KSPCreate(PETSC_COMM_WORLD, &ksp));
  PetscCall(KSPSetType(ksp, KSPFGMRES));
  PetscCall(KSPSetOperators(ksp, AplusJ, AplusJ));
  PetscCall(KSPSetNormType(ksp, KSP_NORM_UNPRECONDITIONED));
  PetscCall(KSPGetTolerances(ksp, nullptr, nullptr, &dtol, &maxits));
  PetscCall(KSPSetTolerances(ksp, 1e-6, 1e-50, dtol, maxits));
  PetscCall(KSPGMRESSetRestart(ksp, 300));
  PetscCall(KSPGetPC(ksp, &pc));
  PetscCall(PCSetType(pc, PCCOMPOSITE));
  PetscCall(PCCompositeSetType(pc, PC_COMPOSITE_SPECIAL));
  PetscCall(PCCompositeAddPCType(pc, PCILU));
  PetscCall(PCCompositeAddPCType(pc, PCSHELL));
  PetscCall(PCCompositeGetPC(pc, 0, &pcA));
  PetscCall(PCCompositeGetPC(pc, 1, &pcJ));
  PetscCall(PCSetOperators(pcA, AplusD, AplusD));
  PetscCall(PCSetOperators(pcJ, JplusD, JplusD));
  PetscCall(PCShellSetContext(pcJ, &test_pc));
  PetscCall(PCShellSetApply(pcJ, smw_apply));
  PetscCall(PCShellSetSetUp(pcJ, smw_setup));
  PetscCall(PCCompositeSpecialSetAlphaMat(pc, D));

  // Solve
  PetscCall(KSPSetFromOptions(ksp));
  PetscCall(KSPSolve(ksp, b, x));

  PetscCall(MatDestroy(&A));
  PetscCall(MatDestroy(&B));
  PetscCall(MatDestroy(&Q));
  PetscCall(MatDestroy(&Acondensed));
  PetscCall(MatDestroy(&Bcondensed));
  PetscCall(MatDestroy(&BT));
  PetscCall(MatDestroy(&J));
  PetscCall(MatDestroy(&AplusJ));
  PetscCall(MatDestroy(&QInv));
  PetscCall(MatDestroy(&D));
  PetscCall(MatDestroy(&AplusD));
  PetscCall(MatDestroy(&JplusD));
  PetscCall(MatDestroy(&U));
  if (rank == 0)
    PetscCall(VecDestroy(&bound));
  PetscCall(VecDestroy(&x));
  PetscCall(VecDestroy(&b));
  PetscCall(VecDestroy(&Qdiag));
  PetscCall(VecDestroy(&DVec));
  PetscCall(ISDestroy(&boundary_is));
  PetscCall(ISDestroy(&bulk_is));
  PetscCall(KSPDestroy(&ksp));
  PetscCall(PetscFree(boundary_indices));
  PetscCall(test_pc.destroy());

#ifdef HAVE_GPERFTOOLS
  // CPU profiling stop
  if (has_cpu_profiling)
    ProfilerStop();
#endif

  PetscCall(PetscFinalize());
  return 0;
}
