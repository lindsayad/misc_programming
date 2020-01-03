void my_vec_view(const NumericVector<Real> &vec) {
  PetscVector<Real> &petsc_vec = const_cast<PetscVector<Real> &>(
      static_cast<const PetscVector<Real> &>(vec));
  VecView(petsc_vec.vec(), 0);
}

void my_vec_view(const DiagonalMatrix<Real> &mat) {
  my_vec_view(mat.diagonal());
}
