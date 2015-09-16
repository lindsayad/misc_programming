#!/usr/bin/env python

from fipy import *
import math
import numpy as np
#
nx = 100
L = 5.e-3 # Gap between needle and water surface (m)
e = 1.6e-19 # Coulombic charge of an electron (C)
eps = 8.85e-12 # Permittivity of free space (F/m)
Vapplied = 7000. # Applied voltage
Rballast = 5.e6 # Resistance of ballast resistor
#
dx = L/nx
#
mesh = Grid1D(nx=nx, dx=dx)
#
phi = CellVariable(name="Potential (V)", mesh=mesh, value=0.)
Efield = -phi.grad
EfieldMag = np.fmax(np.fabs(Efield), 10)
#
inidensity = 1.e20 # (m^-3)
electrons = CellVariable(name="electrons (m^-3)", mesh=mesh, value=inidensity)
ions = CellVariable(name="ions", mesh=mesh, value=inidensity)
rho = e * (ions - electrons) # Charge density
#
alpha = .35 * np.exp(-1.65e3 / EfieldMag) # Ionization coefficient (1/m)
We = -60.6*Efield**.75 # Electron velocity vector (m/s)
Wp = 2.43 / 100 * Efield # Ion velocity vector (m/s)
De = 1800. / (100**2) # Electron diffusion coefficient
Dp = .046 / (100**2) # Ion diffusion coefficient
PlasmaCurrent = e * (Wp * ions - (We * electrons - De * electrons.grad))
Vanode = Vapplied - PlasmaCurrent * Rballast
Vcathode = 0.
#
phi.equation = (DiffusionTerm(coeff = eps) + rho == 0.)
electrons.equation = (TransientTerm(coeff = 1.) + PowerLawConvectionTerm(coeff = We) - DiffusionTerm(coeff = De) == alpha * electrons * np.fabs(We)) 
ions.equation = (TransientTerm(coeff = 1.) + PowerLawConvectionTerm(coeff = Wp) == alpha * electrons * np.fabs(We)) 
phi.constrain(Vanode, mesh.facesLeft)
phi.constrain(Vcathode, mesh.facesRight)
#
eqn = phi.equation & electrons.equation & ions.equation
viewer= Viewer(vars=(phi, electrons, ions))
#
for t in range(1e-8)
	phi.updateOld()
	electrons.updateOld()
	ions.updateOld()
	eqn.solve(dt=1.e-11)
	viewer.plot()
#
# phi.equation.solve(var=phi)
#
raw_input("Press any key to continue...")

