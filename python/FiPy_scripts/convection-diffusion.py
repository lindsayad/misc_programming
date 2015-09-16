#!/usr/bin/env python
#
diffCoeff = 1.
convCoeff = (10.,)
#
from fipy import *
L = 10.
nx = 10
mesh = Grid1D(dx=L/nx, nx=nx)
valueLeft = 0.
valueRight = 1.
#
var = CellVariable(mesh=mesh, name="variable")
var.constrain(valueLeft, mesh.facesLeft)
var.constrain(valueRight, mesh.facesRight)
#
eq = (DiffusionTerm(coeff=diffCoeff) + ExponentialConvectionTerm(coeff=convCoeff))
eq.solve(var=var)
#
axis = 0
x = mesh.cellCenters[axis]
CC = 1. - numerix.exp(-convCoeff[axis] * x / diffCoeff)
DD = 1. - numerix.exp(-convCoeff[axis] * L / diffCoeff)
analyticalArray = CC/DD
print var.allclose(analyticalArray, rtol = 1e-5, atol = 1e-5)
viewer = Viewer(vars=(var,analyticalArray))
viewer.plot()

