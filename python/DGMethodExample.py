# This code is adapted from the MATLAB code of Beatrice Riviere in her excellent text: Discontinuous Galerkin Methods for Solving Elliptic and Parabolic Equations
import numpy as np
import scipy.sparse.linalg as la_sparse
import matplotlib.pyplot as plt

def DGsimplesolve(nel,ss,penal):

    # local matrices
    Amat = nel * np.array([[0, 0, 0], [0, 4.0, 0], [0, 0, 16.0/3]])
    Bmat = nel * np.array([[penal, 1.0-penal, -2.0+penal], [-ss-penal, -1.0+ss-penal, 2.0-ss-penal], [2.0*ss+penal, 1.0-2.0*ss-penal, -2.0+2.0*ss+penal]])
    Cmat = nel * np.array([[penal, -1.0+penal, -2.0+penal], [ss+penal, -1.0+ss+penal, -2.0+ss+penal], [2.0*ss+penal, -1.0+2.0*ss+penal, -2.0+2.0*ss+penal]])
    Dmat = nel * np.array([[-penal, -1.0+penal, 2.0-penal], [-ss-penal, -1.0+ss+penal, 2.0-ss-penal], [-2.0*ss-penal, -1.0+2.0*ss+penal, 2.0-2.0*ss-penal]])
    Emat = nel * np.array([[-penal, 1.0-penal, 2.0-penal], [ss+penal, -1.0+ss+penal, -2.0+ss+penal], [-2.0*ss-penal, 1.0-2.0*ss-penal, 2.0-2.0*ss-penal]])
    F0mat = nel * np.array([[penal, 2.0-penal, -4.0+penal], [-2.0*ss-penal, -2.0+2.0*ss+penal, 4.0-2.0*ss-penal], [4.0*ss+penal, 2.0-4.0*ss-penal, -4.0+4.0*ss+penal]])
    FNmat = nel * np.array([[penal, -2.0+penal, -4.0+penal], [2.0*ss+penal, -2.0+2.0*ss+penal, -4.0+2.0*ss+penal], [4.0*ss+penal, -2.0+4.0*ss+penal, -4.0+4.0*ss+penal]])

    # dimension of local matrices
    locdim = 3

    # dimension of global matrix
    glodim = nel * locdim

    # initialize to zero matrix and RHS vector
    Aglobal = np.zeros((glodim,glodim))
    rhsglobal = np.zeros(glodim)

    # Gauss quadrature weights and points
    wg = np.array([1.0, 1.0])
    sg = np.array([-0.577350269189, 0.577350269189])

    # Assemble global matrix and RHS
    # First block row
    for ii in range(0,locdim):
        for jj in range(0,locdim):
            Aglobal[ii][jj] = Aglobal[ii][jj] + Amat[ii][jj] + F0mat[ii][jj] + Cmat[ii][jj]
            je = locdim + jj
            Aglobal[ii][je] = Aglobal[ii][je] + Dmat[ii][jj]
    # Compute RHS
    rhsglobal[0] = nel * penal
    rhsglobal[1] = nel*penal*(-1.0) - ss*2.0*nel
    rhsglobal[2] = nel*penal + ss*4.0*nel
    for ig in range(0,2):
        rhsglobal[0] = rhsglobal[0] + wg[ig]*sourcef((sg[ig]+1)/(2.0*nel))/(2.0*nel)
        rhsglobal[1] = rhsglobal[1] + wg[ig]*sg[ig]*sourcef((sg[ig]+1)/(2.0*nel))/(2.0*nel)
        rhsglobal[2] = rhsglobal[2] + wg[ig]*sg[ig]*sg[ig]*sourcef((sg[ig]+1)/(2.0*nel))/(2.0*nel)

    # Intermediate block rows
    # Loop over elements
    for i in range(2,nel):
        for ii in range(0,locdim):
            ie = ii + (i-1)*locdim
            for jj in range(0,locdim):
                je = jj + (i-1)*locdim
                Aglobal[ie][je] = Aglobal[ie][je] + Amat[ii][jj] + Bmat[ii][jj] + Cmat[ii][jj]
                je = jj + (i-2)*locdim
                Aglobal[ie][je] = Aglobal[ie][je] + Emat[ii][jj]
                je = jj + i*locdim
                Aglobal[ie][je] = Aglobal[ie][je] + Dmat[ii][jj]
            # Compute RHS
            for ig in range(0,2):
                rhsglobal[ie] = rhsglobal[ie] + wg[ig]*(sg[ig]**ii)*sourcef((sg[ig]+2.0*(i-1)+1.0)/(2.0*nel))/(2.0*nel)

    # Last block row
    for ii in range(0,locdim):
        ie = ii+(nel-1)*locdim
        for jj in range(0,locdim):
            je = jj+(nel-1)*locdim
            Aglobal[ie][je] = Aglobal[ie][je] + Amat[ii][jj] + FNmat[ii][jj] + Bmat[ii][jj]
            je = jj+(nel-2)*locdim
            Aglobal[ie][je] = Aglobal[ie][je] + Emat[ii][jj]
        # Compute RHS
        for ig in range(0,2):
            rhsglobal[ie] = rhsglobal[ie] + wg[ig]*(sg[ig]**ii)*sourcef((sg[ig]+2.0*(nel-1)+1.0)/(2.0*nel))/(2.0*nel)
    
    Aglobalinv = np.linalg.inv(Aglobal)
    ysol = np.dot(Aglobalinv,rhsglobal)
    
    return (Aglobal,rhsglobal,ysol)

def sourcef(xval):

    # source function for exact solution=(1-x)*exp(-x**2)
    yval = -(2.0*xval-2.0*(1.0-2.0*xval)+4.0*xval*(xval-xval**2))*np.exp(-xval*xval)
    # yval = 12.0*xval**2
    return yval

def ZerothMonomial(x,n,nel):
    return 1.0

def FirstMonomial(x,n,nel):
    h = 1.0/nel
    xn = n*h
    xnp1 = (n+1)*h
    xnhalf = 0.5*(xn + xnp1)
    f = 2.0*(x-xnhalf)/(xnp1 - xn)
    return f

def SecondMonomial(x,n,nel):
    h = 1.0/nel
    xn = n*h
    xnp1 = (n+1)*h
    xnhalf = 0.5*(xn + xnp1)
    f = 4.0*(x-xnhalf)**2/(xnp1-xn)**2
    return f

def exactSolution(x):
    return (1.0-x)*np.exp(-x**2)
    # return 1.0-x**4


# def main():
nel = 4
h = 1.0/nel
ss = 1
penal = 1
felina = DGsimplesolve(nel,ss,penal)
locdim = 3
uh = np.zeros(nel)
x = np.zeros(nel)
u = np.zeros(nel)
line = np.zeros(nel)

for n in range(0,nel):
    # u(x)[n] = felina[2][n*locdim]*ZerothMonomial(x,n,ne) + felina[2][n*locdim+1]*FirstMonomial(x,n,ne) + felina[2][n*locdim+2]*SecondMonomial(x,n,ne)
    x[n] = n*h + h/2
    uh[n] = felina[2][n*locdim]*ZerothMonomial(x[n],n,nel)
    u[n] = exactSolution(x[n])
    line[n] = 1.0-x[n]
    
plt.plot(x,uh,label='approximate')
plt.plot(x,u,label='exact')
# plt.plot(x,line,label='line')
plt.legend(loc=0)
plt.show()

# if __name__ == '__main__':
#     main()
