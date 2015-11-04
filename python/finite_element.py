import numpy as np
import matplotlib.pyplot as plt

# Dirichlet formulation where cells are shifted by h/2

length = 1.0
N = 10 # number of cells
numNodes = N + 1 # number of nodes
numUnknownNodes = numNodes - 2
m = numUnknownNodes
h = length/N

# dt below is the maximum value that ensures no oscillations will grow for an explicit time stepping scheme

# dt = h
dt = h**3/2
t = 0.0

# Initialization of the problem

position = np.zeros(numNodes)
q = np.zeros(numNodes) # Solution vector including BCs
u = np.zeros(m) # Solution vector without BCs
S = np.zeros(m)
S_conv = np.zeros(m)
S_rxn = np.zeros(m)
M = np.zeros((m,m)) # Mass matrix
A = np.zeros((m,m)) # Diffusion matrix
C = np.zeros((m,m)) # Convection matrix
Rxn = np.zeros((m,m)) # Reaction matrix
q[0] = 1.0
q[numNodes-1] = 0.0

for i in range(0,numNodes):
    position[i] = i*h
A[0][0] = -2.0
A[0][1] = 1.0
A[m-1][m-2] = 1.0
A[m-1][m-1] = -2.0
C[0][1] = 1.0
C[m-1][m-2] = -1.0
M[0][0] = 2.0/3.0
M[0][1] = 1.0/6.0
M[m-1][m-2] = 1.0/6.0
M[m-1][m-1] = 2.0/3.0
Rxn[0][0] = 2.0/3.0
Rxn[0][1] = 1.0/6.0
Rxn[m-1][m-2] = 1.0/6.0
Rxn[m-1][m-1] = 2.0/3.0
for i in range(1,m-1):
    # create diffusion matrix
    A[i,i-1] = 1.0
    A[i,i] = -2.0
    A[i,i+1] = 1.0
    # create convection matrix
    C[i][i+1] = 1.0
    C[i][i-1] = -1.0
    # create mass matrix
    M[i][i-1] = 1.0/6.0
    M[i][i] = 2.0/3.0
    M[i][i+1] = 1.0/6.0
    # create reaction matrix
    Rxn[i][i-1] = 1.0/6.0
    Rxn[i][i] = 2.0/3.0
    Rxn[i][i+1] = 1.0/6.0
A = 1/h**2 * A
C = 1/(2*h) * C

# use this loop for mass lumping
# for i in range(0,m):
#     sum = 0
#     for j in range(0,m):
#         sum += M[i][j]
#         M[i][j] = 0.0
#     M[i][i] = sum
# Minv = np.linalg.inv(M)

# Add in effect of Dirichlet boundary conditions
S[0] = 1.0
S = 1/h**2 * S
S_conv[0] = -1.0
S_conv = 1/(2*h) * S_conv
S_rxn[0] = 1.0/6.0
I = np.zeros((m,m))
for i in range(0,m):
    I[i][i] = 1.0

output = q
np.set_printoptions(precision=3)
plt.clf()

# Value of theta determines time stepping scheme.
# Forward Euler = 0
# Crank Nicholson = 0.5
# Backwrad Euler = 1.0
Theta = 0.0
j = 0
B = M - Theta*dt*(A-5.0*Rxn)
while t < 1.0:
    j += 1
    t = t + dt

    b = np.dot(M,u)+(1-Theta)*np.dot(dt*(A-5.0*Rxn),u) + dt*(S-5.0*S_rxn)
    Bmod=np.zeros((m,m))
    bmod = np.zeros(m)
    Bmod[0][1]=B[0][1]/B[0][0]
    bmod[0] = b[0]/B[0][0]
    for i in range(1,m-1):
        Bmod[i][i+1] = B[i][i+1]/(B[i][i]-B[i][i-1]*Bmod[i-1][i])
    for i in range(1,m):
        bmod[i] = (b[i]-B[i][i-1]*bmod[i-1])/(B[i][i]-B[i][i-1]*Bmod[i-1][i])
    u[m-1] = bmod[m-1]
    for i in range(m-2,-1,-1):
        u[i] = bmod[i]-Bmod[i][i+1]*u[i+1]

    for i in range(0,m):
        q[i+1]=u[i]
    output = np.concatenate((output,q),axis=0)
    plt.plot(position,output[j*(numNodes):(j+1)*(numNodes)])
# plt.plot(position,q,label='Advection diffusion reaction')

# j = 0
# t = 0
# u = np.zeros(m) # Solution vector without BCs
# while t < 1.0:
#     j += 1
#     t = t + dt

#     # Forward Euler, explicit
#     if discType==0:
#         u = u + dt*(np.dot(A-C,u)+S-S_conv)
#     for i in range(0,m):
#         q[i+1]=u[i]
# plt.plot(position,q,label='Advection diffusion')

# j = 0
# t = 0
# u = np.zeros(m) # Solution vector without BCs
# while t < 1.0:
#     j += 1
#     t = t + dt

#     # Forward Euler, explicit
#     if discType==0:
#         u = u + dt*(np.dot(A,u)+S)
#     for i in range(0,m):
#         q[i+1]=u[i]
# plt.plot(position,q,label='diffusion')

# j = 0
# t = 0
# u = np.zeros(m) # Solution vector without BCs
# while t < 1.0:
#     j += 1
#     t = t + dt

#     # Forward Euler, explicit
#     if discType==0:
#         u = u + dt*(np.dot(A+Rxn,u)+S)
#     for i in range(0,m):
#         q[i+1]=u[i]
# plt.plot(position,q,label='Diffusion reaction')
# plt.legend(loc=1)

# if discType==0:
#     plt.savefig('Forward_Euler.png',format='png')
# elif discType==1:
#     plt.savefig('Backward_Euler.png',format='png')
# elif discType==2:
#     plt.savefig('Crank_Nicholson.png',format='png')
# plt.title('Crank-Nicholson time discretization')
plt.show()
