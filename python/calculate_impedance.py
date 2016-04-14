import impedance as imp
import math
from sympy.physics import units as u
from sympy import sqrt, re, im, I
from constants import constants as c
import numpy as np
import matplotlib.pyplot as plt

d = .05 * u.m
A = 9.6 * (u.cm)**2
mu = 1e-2 * (u.m)**2 / (u.V * u.s)
# n_0 = 1e17 / (u.m)**3
m = 9.11e-31 * u.kg
T_g = 3000 * u.K

n_g = 1.01e5 * u.Pa / (c.kB * T_g)
alpha = 2.1e-29 * (u.m)**3
nu_em = n_g * sqrt(math.pi * alpha * c.e**2 / (m * c.eps0))
eps_r = 1.

def indep_array(start, finish, num_steps):
    x = np.zeros(num_steps)
    for i in range(0, num_steps):
        x[i] = start * ((finish / start) ** (1. / (num_steps - 1.))) ** i
    return x

def impedance_arrays(dens_points, freq_points):
    for i in range(0, len(dens_points)):
        for j in range(0, len(freq_points)):
            eps, Yp, Zp = imp.impedance(freq_points[j] / u.s, m, dens_points[i], A, d, eps_r, nu_m = nu_em)
            Rp[i][j] = re(Zp) / u.ohm
            Xp[i][j] = im(Zp) / u.ohm
    return Rp, Xp

dens_start, dens_end, dens_steps = 1e15, 1e21, 50
dens_points = indep_array(dens_start, dens_end, dens_steps)
freq_points = np.array([.1e6, 2e6, 13e6, 60e6, 162e6])
Rp_gas, Xp_gas = impedance_arrays(dens_points, freq_points)

# for i in range(0, nf):
#     eps, Yp, Zp = imp.impedance(f[i] / u.s, m, n_0, A, d, eps_r, nu_m = nu_em)
#     Rp_gas[i] = re(Zp) / u.ohm
#     Xp_gas[i] = im(Zp) / u.ohm

# plt.plot(f, Rp_gas)
# plt.yscale('log')
# plt.xscale('log')
# plt.savefig('Rp_vs_f.eps', format = 'eps')
# plt.show()
# plt.plot(f, Xp_gas)

# print "Plasma resistance in Ohms is " + str(Rp)
# print "Plasma reactance in Ohms is " + str(Xp)

# RB = d * nu_em * m / (A * c.e**2 * n_0)
# LB = RB / nu_em
# CB = c.eps0 * A / d
# ZRB = RB
# ZLB = I * w * LB
# ZCB = 1. / (I * w * CB)
# Zp = 1. / (1. / ZCB + 1. / (ZRB + ZLB))
# Rp = re(Zp) / u.ohm
# Xp = im(Zp) / u.ohm

# print "Plasma resistance in Ohms from Brandon model is " + str(Rp)
# print "Plasma reactance in Ohms from Brandon model is " + str(Xp)

# # Properties for Na or Cl in water
# diff = 2e-9 * (u.m)**2 / u.s # reference Ranga
# T_l = 300 * u.K
# mu = diff * c.e / (c.kB * T_l)
# mass_Cl = 13.3 * u.mg / u.l # reference Raleigh municipal plant
# weight_Cl = 35.5 * u.g / u.mol
# n_Cl = mass_Cl / weight_Cl * u.avogadro
# m = weight_Cl / u.avogadro
# eps_r = 80.
# d = 1. * u.mm

# nu_m = c.e / (m * mu)
# eps, Yp, Zp = imp.impedance(f, m, n_Cl, A, d, eps_r, nu_m = nu_m)
# Rp = re(Zp) / u.ohm
# Xp = im(Zp) / u.ohm
# print "Water resistance in Ohms is " + str(Rp)
# print "Water reactance in Ohms is " + str(Xp)
