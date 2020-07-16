void dgetrf_(int *, int *, double *, int *, int*, int*);

int main()
{
  int M = 2, N = 2, LDA = 2, INFO = 0;

  int pivots[] = {1, 0};

  double data[] = {-1.0755711889275745e-07,
                   -6.1091865142262008e-15,
                   6.5708650024865796e-22,
                   -2.4000593701562563e-06};

  dgetrf_(&M, &N, data, &LDA, pivots, &INFO);

}
