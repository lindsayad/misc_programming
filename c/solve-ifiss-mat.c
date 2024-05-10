static char help[] = "(Attempts to) apply the 2023 preconditioner of Benzi and Faccio\n\n";

#include <petscmat.h>
#include <petscviewer.h>
#include <petscvec.h>
#include <petscis.h>
#include <petscksp.h>
#include <string>
#include <iostream>
#include <cassert>

int
main(int argc, char ** args)
{
  Mat A, B, Q, Acondensed, Bcondensed, BT, J, AplusJ, QInv, D, AplusD, JplusD;
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
  PetscScalar gamma = 100;
  PetscScalar alpha = .01;
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

  // Create sum
  PetscCall(MatDuplicate(Acondensed, MAT_COPY_VALUES, &AplusJ));
  PetscCall(MatAXPY(AplusJ, 1.0, J, DIFFERENT_NONZERO_PATTERN));

  // Create x and b
  PetscCall(MatCreateVecs(AplusJ, &x, &b));
  PetscCall(PetscRandomCreate(PETSC_COMM_SELF, &rctx));
  PetscCall(VecSetRandom(x, rctx));
  PetscCall(PetscRandomDestroy(&rctx));
  PetscCall(MatMult(AplusJ, x, b));

  // Compute preconditioner operators
  PetscCall(MatGetLocalSize(Acondensed, &condensed_am, nullptr));
  PetscCall(MatCreate(PETSC_COMM_SELF, &D));
  PetscCall(MatSetType(D, MATSEQAIJ));
  PetscCall(MatSetSizes(D, condensed_am, condensed_am, condensed_am, condensed_am));
  static constexpr PetscScalar zero = 0;
  for (PetscInt i = 0; i < condensed_am; ++i)
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
  PetscCall(PCSetOperators(pckspA, AplusD, AplusD));
  PetscCall(PCSetOperators(pcA, AplusD, AplusD));
  PetscCall(PCSetOperators(pckspJ, JplusD, JplusD));
  PetscCall(PCSetOperators(pcJ, JplusD, JplusD));
  PetscCall(PCCompositeSpecialSetAlphaMat(pc, D));

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
  PetscCall(MatDestroy(&D));
  PetscCall(MatDestroy(&AplusD));
  PetscCall(MatDestroy(&JplusD));
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
