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
m_gas = 29*1.66e-27
gamma_i = 0.1
# The ionization energy of nitrogen is 15.6 eV
# The ionizaiton energy of oxygen is 12.1 eV
# For a terrible first start let's use the average of these values
EIon = 13.85
# Dirichlet electron energy at the cathode boundary
right_bound_en = 1

# initialize grid and variables
L = 5e-3
NC = 1400
NT = NC+2
h = L/NC
ini_density=1e17
ini_energy = 1.0
end_time = 4e-9
output_time = 1e-10

# Cell centered variables
phi = np.zeros(NT)
elec = np.full(NT,ini_density)
pion = np.full(NT,ini_density)
energy = np.full(NT,ini_energy)
alpha = np.zeros(NC)
eta = np.zeros(NC)
elastic = np.zeros(NC)
fldnorm = np.zeros(NC)
sigma = np.zeros(NC)
mobcenter = np.zeros(NC)
sflux_elec = np.zeros(NT)
sflux_pion = np.zeros(NT)
sflux_en = np.zeros(NT)
src_elec = np.zeros(NT)
src_pion = np.zeros(NT)
src_en = np.zeros(NT)

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
f_en = np.zeros(NT-1)
grad_elec = np.zeros(NT-1)
grad_pion = np.zeros(NT-1)
grad_energy = np.zeros(NT-1)
Energy_face = np.zeros(NT-1)
elec_face = np.zeros(NT-1)

# Build lookup tables
LUT = np.genfromtxt('mob_en.txt',delimiter=',',dtype=float)
Emobint = LUT[:,:1]
mobint = LUT[:,1]
LUT = np.genfromtxt('diff_en.txt',delimiter=',',dtype=float)
Ediffint = LUT[:,:1]
diffint = LUT[:,1]
LUT = np.genfromtxt('alpha_en.txt',delimiter=',',dtype=float)
Ealphaint = LUT[:,:1]
alphaint = LUT[:,1]
LUT = np.genfromtxt('eta_en.txt',delimiter=',',dtype=float)
Eetaint = LUT[:,:1]
etaint = LUT[:,1]
# LUT = np.genfromtxt('mean_en.txt',delimiter=' ',dtype=float)
# Emean_enint = LUT[:,:1]
# mean_enint = LUT[:,1]
LUT = np.genfromtxt('elastic_en.txt',delimiter=',',dtype=float)
Eelasticint = LUT[:,:1]
elasticint = LUT[:,1]
del LUT

# Plotting variables
ccposition = np.arange(h/2,L+h/2,h)
fcposition = np.arange(0,L+h,h)
position = np.insert(ccposition,0,0.0)
position = np.append(position,L)
elecplot = np.zeros(NT)
pionplot = np.zeros(NT)
phiplot = np.zeros(NT)
enplot = np.zeros(NT)
cclist = [elec,pion,phi,energy]
plot_list = [elecplot,pionplot,phiplot,enplot,fld]
ccplot_list = [elecplot,pionplot,phiplot,enplot]

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

file_list = ['elec.txt','pion.txt','phi.txt','en.txt','fld.txt']
filecc_list = ['elec.txt','pion.txt','phi.txt','en.txt']
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

    # Compute important face centered properties
    for i in range(0,NT-1):
        fld[i]=-(phi[i+1]-phi[i])/h
        Energy_face[i] = (energy[i]+energy[i+1])/2
        tree = KDTree(Emobint)
        dist, ind = tree.query(np.absolute(Energy_face[i,newaxis]),k=2)
        E1, E2 = dist.T
        mob1, mob2 = mobint[ind].T
        mob[i] = E1/(E1 + E2) * mob2 + E2/(E1 + E2) * mob1
        tree = KDTree(Ediffint)
        dist, ind = tree.query(np.absolute(Energy_face[i,newaxis]),k=2)
        E1, E2 = dist.T
        diff1, diff2 = diffint[ind].T
        diff[i] = E1/(E1 + E2) * diff2 + E2/(E1 + E2) * diff1
        v[i] = -mob[i]*fld[i]
    vth_right = 1.6 * sqrt(elem_c * Energy_face[NT-2] / m_elec)
    vth_left = 1.6 * sqrt(elem_c * Energy_face[0] / m_elec)
    
    # Calculate some important cell centered quantities
    for i in range(0,NC):
        fldnorm[i]=fabs((phi[i+2]-phi[i])/(2*h))
        tree = KDTree(Ealphaint)
        dist, ind = tree.query(np.absolute(energy[i,newaxis]),k=2)
        E1, E2 = dist.T
        alpha1, alpha2 = alphaint[ind].T
        alpha[i] = E1/(E1 + E2) * alpha2 + E2/(E1 + E2) * alpha1
        tree = KDTree(Eetaint)
        dist, ind = tree.query(np.absolute(energy[i,newaxis]),k=2)
        E1, E2 = dist.T
        eta1, eta2 = etaint[ind].T
        eta[i] = E1/(E1 + E2) * eta2 + E2/(E1 + E2) * eta1
        tree = KDTree(Eelasticint)
        dist, ind = tree.query(np.absolute(energy[i,newaxis]),k=2)
        E1, E2 = dist.T
        elastic1, elastic2 = elasticint[ind].T
        elastic[i] = E1/(E1 + E2) * elastic2 + E2/(E1 + E2) * elastic1
        mobcenter[i] = (mob[i]+mob[i+1])/2
        sigma[i] = mobcenter[i] * elem_c * elec[i+1]
    
    # Fill electron, ion, and energy ghost cells
    if fld[NT-2] > 0:
        pion[NT-1] = pion[NT-2]
    else:
        pion[NT-1] = pion[NT-2] * (2*Di+fld[NT-2]*mui*h) / (2*Di-fld[NT-2]*mui*h)
    if fld[0] > 0:
        pion[0] = pion[1] * (2*Di-fld[0]*mui*h) / (2*Di+fld[0]*mui*h)
    else:
        pion[0] = pion[1]
    # Going to assume that all the electron flux at the cathode is due to drift flux. Because of the high electric field, I'm going to 
    # assume that the net electron flux at the cathode is <= 0. As a consequence of these assumptions, we have a Neumann zero condition
    # for the electrons at the cathode.
    # elec[NT-1] = (2*diff[NT-2]*elec[NT-2] + fld[NT-2]*gamma_i*h*mui*pion[NT-2] + fld[NT-2]*gamma_i*h*mui*pion[NT-1] - fld[NT-2]*h*mob[NT-2]*elec[NT-2])/(2*diff[NT-2]+fld[NT-2]*h*mob[NT-2])
    elec[NT-1] = elec[NT-2]
    elec[0] = elec[1] * (4*diff[0] + 2*fld[0]*h*mob[0] - h*vth_left) / (4*diff[0] - 2*fld[0]*h*mob[0] + h*vth_left)
    for i in range(0,NT-1):
        elec_face[i] = (elec[i]+elec[i+1])/2
    energy[NT-1] = 2 * right_bound_en - energy[NT-2]
    # This is currently the troublesome boundary condition. This 
    # is the anode. Setting the boundary energy to zero here doesn't
    # make any physical sense. Electrons are being accelerated 
    # towards the anode, so the idea that their energy there is zero
    # is preposterous
    energy[0] = 0.2*(-12.0*diff[0]*elec[0] + 12.0*diff[0]*elec[1] + 6.0*elec[0]*fld[0]*h*mob[0] - 5.0*elec[1]*energy[1]*h*vth_left + 6.0*elec[1]*fld[0]*h*mob[0])/(elec[0]*h*vth_left)

    # Calculate electron, ion, and energy fluxes
    # using a first-order upwind scheme for advection
    # at all but the boundary faces
    for i in range(0,NT-1):
        grad_elec[i] = (elec[i+1]-elec[i])/h
        grad_energy[i] = (energy[i+1] - energy[i])/h
    for i in range(1,NT-2):
        if v[i] >= 0:
            f_elec[i] = v[i]*elec[i] - diff[i]*grad_elec[i]
            f_en[i] = 5.0/3*energy[i]*f_elec[i]-5.0/3*(elec[i]+elec[i+1])/2*diff[i]*grad_energy[i]
        elif v[i] < 0:
            f_elec[i] = v[i]*elec[i+1] - diff[i]*grad_elec[i]
            f_en[i] = 5.0/3*energy[i+1]*f_elec[i]-5.0/3*(elec[i]+elec[i+1])/2*diff[i]*grad_energy[i]
        grad_pion[i] = (pion[i+1] - pion[i])/h
        if fld[i] >= 0:
            f_pion[i] = mui*fld[i]*pion[i] - Di*grad_pion[i]
        elif fld[i] < 0:
            f_pion[i] = mui*fld[i]*pion[i+1] - Di*grad_pion[i]
    # f_elec[0] = v[0]*(elec[0]+elec[1])/2 - diff[0]*grad_elec[0]
    f_elec[0] = v[0]*elec[1] - diff[0]*grad_elec[0]
    f_en[0] = 5.0/3*energy[1]*f_elec[0]-5.0/3*(elec[0]+elec[1])/2 * diff[0] * grad_energy[0]
    f_pion[0] = mui*fld[0]*(pion[0]+pion[1])/2 - Di * grad_pion[0]
    # f_elec[NT-2] = v[NT-2]*(elec[NT-2]+elec[NT-1])/2 - diff[NT-2]*grad_elec[NT-2]
    f_elec[NT-2] = v[NT-2] * elec[NT-1]
    # f_en[NT-2] = v[NT-2]*right_bound_en*(elec[NT-2]+elec[NT-1])/2-5.0/3*(elec[NT-2]+elec[NT-1])/2 * diff[NT-2] * grad_energy[NT-2]
    f_en[NT-2] = v[NT-2]*right_bound_en*elec[NT-1]-5.0/3*(elec[NT-2]+elec[NT-1])/2 * diff[NT-2] * grad_energy[NT-2]
    f_pion[NT-2] = mui*fld[NT-2]*(pion[NT-2]+pion[NT-1])/2 - Di * grad_pion[NT-2]
    
    # Time stepping restrictions based on Jannis code
    v_max = np.amax(np.absolute(v))
    dt_cfl = 0.7 * h / max(v_max,vth_left,vth_right)
    dt_diff = 0.25 * h**2 / np.amax(diff)
    dt_drt = eps0 / np.amax(sigma)
    dt_alpha = 1 / np.amax(mobcenter * fldnorm * alpha)
    dt_max = 1e-14
    dt = 0.8 * min(1/(1/dt_cfl + 1/dt_diff), dt_drt, dt_alpha)
    
    # Calculate electron source from volume process and fluxes through surfaces
    # Then propagate solution forward
    for i in range(1,NT-1):
        sflux_elec[i] = (f_elec[i-1]-f_elec[i]) / h
        sflux_pion[i] = (f_pion[i-1]-f_pion[i]) / h
        sflux_en[i] = (f_en[i-1]-f_en[i]) / h
        src_elec[i] = (alpha[i-1]-eta[i-1]) * fldnorm[i-1] * mobcenter[i-1] * elec[i]
        src_pion[i] = (alpha[i-1]-eta[i-1]) * fldnorm[i-1] * mobcenter[i-1] * elec[i]
        # First term here is Joule heating term
        src_en[i] = -(f_elec[i-1]*fld[i-1]+f_elec[i]*fld[i]) / 2 - alpha[i-1] * fldnorm[i-1] * mobcenter[i-1] * elec[i] * EIon - 3.0 * elastic[i-1] * fldnorm[i-1] * mobcenter[i-1] * elec[i] * m_elec / m_gas * 2.0 / 3.0 * energy[i]
        elec[i] = elec[i] + dt * (sflux_elec[i])
        pion[i] = pion[i] + dt * (sflux_pion[i])
        energy[i] = energy[i] + dt * (sflux_en[i]) / elec[i]
        # elec[i] = elec[i] + dt * (sflux_elec[i] + src_elec[i])
        # pion[i] = pion[i] + dt * (sflux_pion[i] + src_pion[i])
        # energy[i] = energy[i] + dt * (sflux_en[i] + src_en[i])

    time = time + dt
    output_watch = output_watch + dt
    j = j + 1
    if output_watch >= output_time:
        output_watch = 0.0
        for p,var in zip(ccplot_list,cclist):
            p[0] = (var[0]+var[1])/2
            p[NT-1] = (var[NT-1]+var[NT-2])/2
        # elecplot[0] = (elec[0]+elec[1])/2
        # pionplot[0] = (pion[0]+pion[1])/2
        # elecplot[NT-1] = (elec[NT-1]+elec[NT-2])/2
        # pionplot[NT-1] = (pion[NT-1]+pion[NT-2])/2
        # phiplot[0] = (phi[0]+phi[1])/2
        # phiplot[NT-1] = (phi[NT-1]+phi[NT-2])/2
        for i in range(1,NT-1):
            for p, var in zip(ccplot_list,cclist):
                p[i] = var[i]
            # elecplot[i] = elec[i]
            # pionplot[i] = pion[i]
            # phiplot[i] = phi[i]
        for file,plot in zip(file_list,plot_list):
            with open(file,'a') as f:
                np.savetxt(f,plot[None],fmt='%.2e',delimiter=', ')
    print dt_cfl, dt_diff, dt_drt, dt_alpha
    print time
