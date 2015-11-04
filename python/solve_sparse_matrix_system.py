# import numpy as np
# from scipy.sparse import csr_matrix, lil_matrix
# from scipy.sparse.linalg import spsolve
# from numpy.linalg import solve, norm
# from numpy.random import rand
L = 10.0
NN = 11
NE = NN-1
h = L/NE
# For Dirichlet problem, number of unknown grid points is reduced by 2
ND = NN - 2
position = np.arange(0,L+L/NE,L/NE)
DC0= 10.0
DC1 = 0.0
u = np.zeros(NN)
u[0] = DC0
u[NN-1] = DC1
A = lil_matrix((ND,ND))
for i in range(0,ND):
    A[i,i] = -2
for i in range(0,ND-1):
    A[i,i+1] = 1
for i in range(1,ND):
    A[i,i-1] = 1
A = 1/h**2*A
BC = np.zeros(ND)
BC[0] = DC0
BC = 1/h**2*BC
Src = np.full(ND,1.0)
b = -Src - BC
A = A.tocsr()
x = spsolve(A,b,use_umfpack=True)
for i in range(0,ND):
    u[i+1]=x[i]
plt.plot(position,u)
plt.show()
