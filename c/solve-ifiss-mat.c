static char help[] = "(Attempts to) apply the 2023 preconditioner of Benzi and Faccio\n\n";

#include <petscmat.h>
#include <petscviewer.h>
#include <petscvec.h>
#include <petscis.h>
#include <petscksp.h>
#include <string>
#include <iostream>
#include <cassert>

PetscErrorCode
create_identity(PetscInt m, Mat & identity)
{
  PetscFunctionBegin;
  PetscCall(MatCreate(PETSC_COMM_SELF, &identity));
  PetscCall(MatSetType(identity, MATSEQAIJ));
  PetscCall(MatSetSizes(identity, m, m, m, m));
  static constexpr PetscScalar one = 1;
  for (PetscInt i = 0; i < m; ++i)
    PetscCall(MatSetValues(identity, 1, &i, 1, &i, &one, INSERT_VALUES));
  PetscCall(MatAssemblyBegin(identity, MAT_FINAL_ASSEMBLY));
  PetscCall(MatAssemblyEnd(identity, MAT_FINAL_ASSEMBLY));
  PetscFunctionReturn(PETSC_SUCCESS);
}

struct SMWPC
{
  Mat U, UT, In, Ik, aI_plus_gammaUTU;
  PC smw_pc, smw_cholesky;
  KSP smw_pc_ksp;
  PetscReal gamma, alpha;

  SMWPC(Mat U_in, Mat In_in, PetscReal gamma_in, PetscReal alpha_in)
    : U(U_in),
      UT(nullptr),
      In(In_in),
      Ik(nullptr),
      aI_plus_gammaUTU(nullptr),
      smw_pc(nullptr),
      gamma(gamma_in),
      alpha(alpha_in)
  {
  }

  ~SMWPC()
  {
    if (UT)
      MatDestroy(&UT);
    if (Ik)
      MatDestroy(&Ik);
    if (aI_plus_gammaUTU)
      MatDestroy(&aI_plus_gammaUTU);
    if (smw_pc)
      PCDestroy(&smw_pc);
  }

  PetscErrorCode setup()
  {
    PetscInt k;

    PetscFunctionBegin;

    // Create UT
    PetscCall(MatTranspose(U, MAT_INITIAL_MATRIX, &UT));

    // Create Ik
    PetscCall(MatGetLocalSize(U, nullptr, &k));
    PetscCall(create_identity(k, Ik));

    // Create sum Mat
    PetscCall(MatMatMult(UT, U, MAT_INITIAL_MATRIX, PETSC_DEFAULT, &aI_plus_gammaUTU));
    PetscCall(MatScale(aI_plus_gammaUTU, gamma));
    PetscCall(MatAXPY(aI_plus_gammaUTU, alpha, Ik, SUBSET_NONZERO_PATTERN));

    PetscCall(PCCreate(PETSC_COMM_SELF, &smw_pc));
    PetscCall(PCSetType(smw_pc, PCKSP));
    PetscCall(PCSetOperators(smw_pc, aI_plus_gammaUTU, aI_plus_gammaUTU));
    PetscCall(PCSetUp(smw_pc));
    PetscCall(PCKSPGetKSP(smw_pc, &smw_pc_ksp));
    PetscCall(KSPGetPC(smw_pc_ksp, &smw_cholesky));
    PetscCall(PCSetType(smw_cholesky, PCCHOLESKY));
    PetscCall(PCSetUp(smw_cholesky));

    PetscFunctionReturn(PETSC_SUCCESS);
  }

  PetscErrorCode apply(Vec x, Vec y)
  {
    Vec w, w2, w3;
    PetscFunctionBegin;
    PetscCall(MatCreateVecs(UT, &w3, &w));
    PetscCall(VecDuplicate(w, &w2));

    // First term
    PetscCall(MatMult(UT, x, w2));
    PetscCall(PCView(smw_pc, nullptr));
    PetscCall(PCApply(smw_pc, w2, w));
    PetscCall(MatMult(U, w, y));
    PetscCall(VecScale(y, -gamma / alpha));

    // Second term
    PetscCall(VecCopy(x, w3));
    PetscCall(VecScale(w3, 1 / alpha));

    PetscCall(VecAXPY(y, 1, w3));

    PetscCall(VecDestroy(&w));
    PetscCall(VecDestroy(&w2));
    PetscCall(VecDestroy(&w3));
    PetscFunctionReturn(PETSC_SUCCESS);
  }
};

int
main(int argc, char ** args)
{
  Mat A, B, Q, Acondensed, Bcondensed, BT, J, AplusJ, QInv, I, AplusI, JplusI, U;
  Vec bound, x, b, Qdiag, DVec;
  PetscBool flg;
  PetscViewer viewer;
  char file[PETSC_MAX_PATH_LEN];
  PetscInt * boundary_indices;
  PetscInt boundary_indices_size, is_start, is_end, am, an, bm, bn, condensed_am, maxits;
  PetscScalar * boundary_indices_values;
  IS boundary_is, bulk_is;
  KSP ksp, kspA, kspJ;
  PC pc, pckspA, pckspJ, pcA, pcJ;
  PetscRandom rctx;
  PetscReal gamma = 100;
  PetscReal alpha = .01;
  PetscReal dtol;

  PetscFunctionBeginUser;
  PetscCall(PetscInitialize(&argc, &args, (char *)0, help));

  auto create_and_load_mat = [&flg, &viewer, &file](const std::string & mat_name, Mat & mat)
  {
    PetscFunctionBeginUser;

    PetscCall(PetscOptionsGetString(
        nullptr, nullptr, std::string("-f" + mat_name).c_str(), file, sizeof(file), &flg));
    PetscCheck(
        flg, PETSC_COMM_SELF, PETSC_ERR_USER, "Must indicate file with the -f<mat_name> option");
    PetscCall(PetscViewerBinaryOpen(PETSC_COMM_SELF, file, FILE_MODE_READ, &viewer));
    PetscCall(MatCreate(PETSC_COMM_SELF, &mat));
    PetscCall(MatSetType(mat, MATSEQAIJ));
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
  PetscCheck(flg, PETSC_COMM_SELF, PETSC_ERR_USER, "Must indicate file with the -fbound option");
  PetscCall(PetscViewerBinaryOpen(PETSC_COMM_SELF, file, FILE_MODE_READ, &viewer));
  PetscCall(VecCreate(PETSC_COMM_SELF, &bound));
  PetscCall(PetscObjectSetName((PetscObject)bound, "bound"));
  PetscCall(VecSetType(bound, VECSEQ));
  PetscCall(VecLoad(bound, viewer));
  PetscCall(PetscViewerDestroy(&viewer));
  PetscCall(VecGetLocalSize(bound, &boundary_indices_size));
  PetscCall(PetscMalloc1(2 * boundary_indices_size, &boundary_indices));
  PetscCall(VecGetArray(bound, &boundary_indices_values));
  for (PetscInt i = 0; i < boundary_indices_size; ++i)
    // Matlab uses 1-based indexing
    boundary_indices[i] = (PetscInt)boundary_indices_values[i] - 1;
  PetscCall(VecRestoreArray(bound, &boundary_indices_values));
  PetscCall(MatGetOwnershipRange(A, &is_start, &is_end));
  assert(is_start == 0);
  // The total number of dofs for a given velocity component
  const auto nc = is_end / 2;
  assert((is_end % 2) == 0);
  // The dof index ordering appears to be all vx dofs and then all vy dofs
  for (PetscInt i = 0; i < boundary_indices_size; ++i)
    boundary_indices[i + boundary_indices_size] = boundary_indices[i] + nc;

  PetscCall(ISCreateGeneral(PETSC_COMM_SELF,
                            2 * boundary_indices_size,
                            boundary_indices,
                            PETSC_OWN_POINTER,
                            &boundary_is));
  PetscCall(ISComplement(boundary_is, is_start, is_end, &bulk_is));

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
  PetscCall(PetscRandomCreate(PETSC_COMM_SELF, &rctx));
  PetscCall(VecSetRandom(x, rctx));
  PetscCall(PetscRandomDestroy(&rctx));
  PetscCall(MatMult(AplusJ, x, b));

  // Compute preconditioner operators
  PetscCall(MatGetLocalSize(Acondensed, &condensed_am, nullptr));
  PetscCall(create_identity(condensed_am, I));
  PetscCall(MatCreateVecs(I, &DVec, nullptr));
  PetscCall(MatGetDiagonal(AplusJ, DVec));
  PetscScalar * xx;
  PetscCall(VecGetArray(DVec, &xx));
  for (PetscInt i = 0; i < condensed_am; ++i)
    xx[i] = 1.0 / PetscSqrtReal(PetscAbsScalar(xx[i]));
  PetscCall(VecRestoreArray(DVec, &xx));
  PetscCall(MatDiagonalScale(AplusJ, DVec, DVec));
  PetscCall(MatDiagonalScale(Acondensed, DVec, DVec));
  PetscCall(MatDiagonalScale(J, DVec, DVec));
  PetscCall(VecPointwiseMult(b, DVec, b));
  PetscCall(MatDuplicate(Acondensed, MAT_COPY_VALUES, &AplusI));
  PetscCall(MatAXPY(AplusI, alpha, I, SUBSET_NONZERO_PATTERN));
  PetscCall(MatDuplicate(J, MAT_COPY_VALUES, &JplusI));
  PetscCall(MatAXPY(JplusI, alpha, I, SUBSET_NONZERO_PATTERN));
  PetscCall(MatDiagonalScale(U, DVec, nullptr));

  // Tryout the SMW PC application
  SMWPC test_pc(U, I, gamma, alpha);
  test_pc.setup();
  Vec test_vec;
  PetscCall(VecDuplicate(x, &test_vec));
  test_pc.apply(x, test_vec);
  VecDestroy(&test_vec);

  // Set preconditioner operators
  PetscCall(KSPCreate(PETSC_COMM_SELF, &ksp));
  PetscCall(KSPSetType(ksp, KSPFGMRES));
  PetscCall(KSPSetOperators(ksp, AplusJ, AplusJ));
  PetscCall(KSPSetNormType(ksp, KSP_NORM_UNPRECONDITIONED));
  PetscCall(KSPGetTolerances(ksp, nullptr, nullptr, &dtol, &maxits));
  PetscCall(KSPSetTolerances(ksp, 1e-6, 1e-50, dtol, maxits));
  PetscCall(KSPGMRESSetRestart(ksp, 300));
  PetscCall(KSPGetPC(ksp, &pc));
  PetscCall(PCSetType(pc, PCCOMPOSITE));
  PetscCall(PCCompositeSetType(pc, PC_COMPOSITE_SPECIAL));
  PetscCall(PCCompositeAddPCType(pc, PCKSP));
  PetscCall(PCCompositeAddPCType(pc, PCKSP));
  PetscCall(PCCompositeGetPC(pc, 0, &pckspA));
  PetscCall(PCCompositeGetPC(pc, 1, &pckspJ));
  PetscCall(PCKSPGetKSP(pckspA, &kspA));
  PetscCall(PCKSPGetKSP(pckspJ, &kspJ));
  PetscCall(KSPSetTolerances(kspA, 1e-8, 1e-50, dtol, maxits));
  PetscCall(KSPSetTolerances(kspJ, 1e-8, 1e-50, dtol, maxits));
  PetscCall(KSPGetPC(kspA, &pcA));
  PetscCall(KSPGetPC(kspJ, &pcJ));
  PetscCall(PCSetType(pcA, PCLU));
  PetscCall(PCSetType(pcJ, PCLU));
  PetscCall(PCFactorSetMatSolverType(pcA, MATSOLVERMUMPS));
  PetscCall(PCFactorSetMatSolverType(pcJ, MATSOLVERMUMPS));
  // We must also set the operators on the PCKSP's otherwise during setup of the composite PC it
  // will detect that its sub-pcs do not have operators attached and then it will attach the system
  // operator
  PetscCall(PCSetOperators(pckspA, AplusI, AplusI));
  PetscCall(PCSetOperators(pcA, AplusI, AplusI));
  PetscCall(PCSetOperators(pckspJ, JplusI, JplusI));
  PetscCall(PCSetOperators(pcJ, JplusI, JplusI));
  PetscCall(PCCompositeSpecialSetAlphaMat(pc, I));

  // Solve
  PetscCall(KSPSetFromOptions(ksp));
  PetscCall(KSPSetFromOptions(kspA));
  PetscCall(KSPSetFromOptions(kspJ));
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
  PetscCall(MatDestroy(&I));
  PetscCall(MatDestroy(&AplusI));
  PetscCall(MatDestroy(&JplusI));
  PetscCall(MatDestroy(&U));
  PetscCall(VecDestroy(&bound));
  PetscCall(VecDestroy(&x));
  PetscCall(VecDestroy(&b));
  PetscCall(VecDestroy(&Qdiag));
  PetscCall(VecDestroy(&DVec));
  PetscCall(ISDestroy(&boundary_is));
  PetscCall(ISDestroy(&bulk_is));
  PetscCall(KSPDestroy(&ksp));
  PetscCall(PetscFinalize());
  return 0;
}
