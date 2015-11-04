import numpy as np
from scipy.sparse import csr_matrix, lil_matrix
from scipy.sparse.linalg import spsolve
from numpy.linalg import solve, norm
from scipy.spatial import KDTree
from math import *
from numpy import newaxis
import matplotlib.pyplot as plt

# constants
elem_c = 1.6e-19
eps0 = 8.85e-12
m_elec = 9.11e-31
gamma_i = 0.1

# initialize grid and variables
L = 5e-3
NC = 1400
NT = NC+2
h = L/NC
ini_density=1e17
end_time = 100e-9
output_time = 1e-9

# Cell centered variables
phi = np.zeros(NT)
elec = np.full(NT,ini_density)
pion = np.full(NT,ini_density)
alpha = np.zeros(NC)
eta = np.zeros(NC)
fldnorm = np.zeros(NC)
sigma = np.zeros(NC)
mobcenter = np.zeros(NC)
sflux_elec = np.zeros(NT)
sflux_pion = np.zeros(NT)
src_elec = np.zeros(NT)
src_pion = np.zeros(NT)

# Face centered variables
fld = np.zeros(NT-1)
mob = np.zeros(NT-1)
diff = np.zeros(NT-1)
mean_en = np.zeros(NT-1)
mui = 3.42/(1.0e4) # Morrow review paper
Di = 0.046/(1.0e4) # Morrow review paper
v = np.zeros(NT-1)
f_elec = np.zeros(NT-1)
f_pion = np.zeros(NT-1)
grad_elec = np.zeros(NT-1)
grad_pion = np.zeros(NT-1)

# Build lookup tables
LUT = np.genfromtxt('mob.txt',delimiter=',',dtype=float)
Emobint = LUT[:,:1]
mobint = LUT[:,1]
LUT = np.genfromtxt('diff.txt',delimiter=',',dtype=float)
Ediffint = LUT[:,:1]
diffint = LUT[:,1]
LUT = np.genfromtxt('alpha.txt',delimiter=',',dtype=float)
Ealphaint = LUT[:,:1]
alphaint = LUT[:,1]
LUT = np.genfromtxt('eta.txt',delimiter=',',dtype=float)
Eetaint = LUT[:,:1]
etaint = LUT[:,1]
LUT = np.genfromtxt('mean_en.txt',delimiter=',',dtype=float)
Emean_enint = LUT[:,:1]
mean_enint = LUT[:,1]
del LUT

# Plotting variables
ccposition = np.arange(h/2,L+h/2,h)
fcposition = np.arange(0,L+h,h)
position = np.insert(ccposition,0,0.0)
position = np.append(position,L)
elecplot = np.zeros(NT)
pionplot = np.zeros(NT)
phiplot = np.zeros(NT)
plot_list = [elecplot,pionplot,phiplot,fld]

# Build potential laplacian matrix
DCphi0= 16.0e3
DCphiL = 0.0
A = lil_matrix((NC,NC))
for i in range(1,NC-1):
    A[i,i] = -2
for i in range(0,NC-1):
    A[i,i+1] = 1
for i in range(1,NC):
    A[i,i-1] = 1
A[0,0] = -3
A[NC-1,NC-1] = -3
A = 1/h**2*A
BC = np.zeros(NC)
BC[0] = 2*DCphi0
BC = 1/h**2*BC

file_list = ['elec.txt','pion.txt','phi.txt','fld.txt']
filecc_list = ['elec.txt','pion.txt','phi.txt']
for file in filecc_list:
    with open(file,'w') as f:
        np.savetxt(file,position[None],fmt='%.2e',delimiter=', ')
with open('fld.txt','w') as f:
    np.savetxt(f,fcposition[None],fmt='%.2e',delimiter=', ')

# Solve
time = 0.0
output_watch = 0.0
j = 0
while time <= end_time:
    rho = pion-elec
    b = -rho[1:NT-1] * elem_c / eps0 - BC
    A = A.tocsr()
    x = spsolve(A,b,use_umfpack=True)
    for i in range(1,NT-1):
        phi[i] = x[i-1]
    phi[0]=2*DCphi0-phi[1]
    phi[NT-1]=2*DCphiL-phi[NT-2]
    for i in range(0,NT-1):
        fld[i]=-(phi[i+1]-phi[i])/h
        tree = KDTree(Emobint)
        dist, ind = tree.query(np.absolute(fld[i,newaxis]),k=2)
        E1, E2 = dist.T
        mob1, mob2 = mobint[ind].T
        mob[i] = E1/(E1 + E2) * mob2 + E2/(E1 + E2) * mob1
        tree = KDTree(Ediffint)
        dist, ind = tree.query(np.absolute(fld[i,newaxis]),k=2)
        E1, E2 = dist.T
        diff1, diff2 = diffint[ind].T
        diff[i] = E1/(E1 + E2) * diff2 + E2/(E1 + E2) * diff1
        tree = KDTree(Emean_enint)
        dist, ind = tree.query(np.absolute(fld[i,newaxis]),k=2)
        E1, E2 = dist.T
        mean_en1, mean_en2 = mean_enint[ind].T
        mean_en[i] = E1/(E1 + E2) * mean_en2 + E2/(E1 + E2) * mean_en1
        v[i] = -mob[i]*fld[i]
    vth_right = 1.6 * sqrt(elem_c * mean_en[NT-2] / m_elec)
    vth_left = 1.6 * sqrt(elem_c * mean_en[0] / m_elec)
    
    # Calculate some important cell centered quantities
    for i in range(0,NC):
        fldnorm[i]=fabs((phi[i+2]-phi[i])/(2*h))
        tree = KDTree(Ealphaint)
        dist, ind = tree.query(fldnorm[i,newaxis],k=2)
        E1, E2 = dist.T
        alpha1, alpha2 = alphaint[ind].T
        alpha[i] = E1/(E1 + E2) * alpha2 + E2/(E1 + E2) * alpha1
        tree = KDTree(Eetaint)
        dist, ind = tree.query(fldnorm[i,newaxis],k=2)
        E1, E2 = dist.T
        eta1, eta2 = etaint[ind].T
        eta[i] = E1/(E1 + E2) * eta2 + E2/(E1 + E2) * eta1
        mobcenter[i] = (mob[i]+mob[i+1])/2
        sigma[i] = mobcenter[i] * elem_c * elec[i+1]
    
    # Fill electron, and ion ghost cells
    if fld[NT-2] > 0:
        pion[NT-1] = pion[NT-2]
    else:
        pion[NT-1] = pion[NT-2] * (2*Di+fld[NT-2]*mui*h) / (2*Di-fld[NT-2]*mui*h)
    if fld[0] > 0:
        pion[0] = pion[1] * (2*Di-fld[0]*mui*h) / (2*Di+fld[0]*mui*h)
    else:
        pion[0] = pion[1]
    # elec[NT-1] = elec[NT-2] * (4*diff[NT-2] - 2*fld[NT-2]*h*mob[NT-2] - h*vth_right) / (4*diff[NT-2] + 2*fld[NT-2] + h*vth_right)
    elec[NT-1] = (2*diff[NT-2]*elec[NT-2] + fld[NT-2]*gamma_i*h*mui*pion[NT-2] + fld[NT-2]*gamma_i*h*mui*pion[NT-1] - fld[NT-2]*h*mob[NT-2]*elec[NT-2])/(2*diff[NT-2]+fld[NT-2]*h*mob[NT-2])
    elec[0] = elec[1] * (4*diff[0] + 2*fld[0]*h*mob[0] - h*vth_left) / (4*diff[0] - 2*fld[0]*h*mob[0] + h*vth_left)
    
    # Calculate electron and ion fluxes
    # Using a first-order upwind scheme for advection
    for i in range(0,NT-1):
        grad_elec[i] = (elec[i+1]-elec[i])/h
        if v[i] >= 0:
            f_elec[i] = v[i]*elec[i] - diff[i]*grad_elec[i]
        elif v[i] < 0:
            f_elec[i] = v[i]*elec[i+1] - diff[i]*grad_elec[i]
        grad_pion[i] = (pion[i+1] - pion[i])/h
        if fld[i] >= 0:
            f_pion[i] = mui*fld[i]*pion[i] - Di*grad_pion[i]
        elif fld[i] < 0:
            f_pion[i] = mui*fld[i]*pion[i+1] - Di*grad_pion[i]
    
    # Time stepping restrictions based on Jannis code
    v_max = np.amax(np.absolute(v))
    dt_cfl = 0.7 * h / v_max
    dt_diff = 0.25 * h**2 / np.amax(diff)
    dt_drt = eps0 / np.amax(sigma)
    dt_alpha = 1 / np.amax(mobcenter * fldnorm * alpha)
    dt = 0.8 * min(1/(1/dt_cfl + 1/dt_diff), dt_drt, dt_alpha)
    
    # Calculate electron source from volume process and fluxes through surfaces
    # Then propagate solution forward
    for i in range(1,NT-1):
        sflux_elec[i] = (f_elec[i-1]-f_elec[i]) / h
        sflux_pion[i] = (f_pion[i-1]-f_pion[i]) / h
        src_elec[i] = (alpha[i-1]-eta[i-1]) * fldnorm[i-1] * mobcenter[i-1] * elec[i]
        src_pion[i] = (alpha[i-1]-eta[i-1]) * fldnorm[i-1] * mobcenter[i-1] * elec[i]
        elec[i] = elec[i] + dt * (sflux_elec[i] + src_elec[i])
        pion[i] = pion[i] + dt * (sflux_pion[i] + src_pion[i])
    time = time + dt
    output_watch = output_watch + dt
    j = j + 1
    if output_watch >= output_time:
        output_watch = 0.0
        elecplot[0] = (elec[0]+elec[1])/2
        pionplot[0] = (pion[0]+pion[1])/2
        elecplot[NT-1] = (elec[NT-1]+elec[NT-2])/2
        pionplot[NT-1] = (pion[NT-1]+pion[NT-2])/2
        phiplot[0] = (phi[0]+phi[1])/2
        phiplot[NT-1] = (phi[NT-1]+phi[NT-2])/2
        for i in range(1,NT-1):
            elecplot[i] = elec[i]
            pionplot[i] = pion[i]
            phiplot[i] = phi[i]
        for file,plot in zip(file_list,plot_list):
            with open(file,'a') as f:
                np.savetxt(f,plot[None],fmt='%.2e',delimiter=', ')
            f.closed
    print dt_cfl, dt_diff, dt_drt, dt_alpha
    print time
