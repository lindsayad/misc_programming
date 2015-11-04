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

dt = h**2/2
t = 0.0

# Initialization of the problem

position = np.zeros(numNodes)
q = np.zeros(numNodes) # Solution vector including BCs
u = np.zeros(m) # Solution vector without BCs
S = np.zeros(m)
S_conv = np.zeros(m)
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
for i in range(1,m-1):
    A[i,i-1] = 1.0
    A[i,i] = -2.0
    A[i,i+1] = 1.0
    C[i][i+1] = 1.0
    C[i][i-1] = -1.0
A = 1/h**2 * A
C = 1/(2*h) * C
for i in range(0,m):
    Rxn[i][i] = -1.0
S[0] = 1.0
S = 1/h**2 * S
S_conv[0] = -1.0
S_conv = 1/(2*h) * S_conv
I = np.zeros((m,m))
for i in range(0,m):
    I[i][i] = 1.0

discType = 2
if discType == 1:
    B = I - dt*(A-C+Rxn) # Backward Euler
if discType == 2:
    B = I-dt/2*(A-C+Rxn) # Crank Nicholson

output = q
np.set_printoptions(precision=3)
plt.clf()

j = 0
while t < 1.0:
    j += 1
    t = t + dt

    # Forward Euler, explicit
    if discType==0:
        u = u + dt*(np.dot(A-C+Rxn,u)+S-S_conv)

    # Implicit
    elif discType==1 or discType==2:
        # Backward Euler
        if discType==1:
            b = u + dt*(S-S_conv)
        # Crank Nicholson
        if discType==2:
            b = np.dot(I+dt/2*(A-C+Rxn),u) + dt*(S-S_conv)
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
plt.title('Crank-Nicholson time discretization')
plt.show()
