import impedance as imp
import math
from sympy.physics import units as u
from sympy import sqrt, re, im, I
from constants import constants as c
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import matplotlib as mpl
from helper_functions import indep_array
rc('text', usetex=True)
mpl.rcParams.update({'font.size': 18})

def delta_func(rho, w):
    delta = sqrt(2. * rho / (w * c.mu0))
    return delta

def R_water(freq_points):
    # mu = 1.74e-7 * u.m ** 2 / (u.s * u.V)
    # n = 3e22 / u.m ** 3
    # sigma = n * c.e * mu
    sigma = 50e-3 / (u.ohm * u.m)
    rho = 1. / sigma
    R_water = np.zeros(len(freq_points))
    for freq, i in zip(freq_points, range(len(freq_points))):
        w = 2. * math.pi * freq / u.s
        delta = delta_func(rho, w)
        if delta > u.mm:
            delta = u.mm
        R_water[i] = u.cm * rho / (delta * u.cm * u.ohm)
    return R_water

def R_aluminum(freq_points):
    rho = 2.82e-8 * u.ohm * u.m
    R_aluminum = np.zeros(len(freq_points))
    for freq, i in zip(freq_points, range(len(freq_points))):
        w = 2. * math.pi * freq / u.s
        delta = delta_func(rho, w)
        if delta > 3. * u.cm:
            delta = 3. * u.cm
        R_aluminum[i] = u.cm * rho / (delta * u.cm * u.ohm)
    return R_aluminum

print "Water skin depth at 162 MHz is " + str(delta_func(1. / (50e-3 / (u.ohm * u.m)), 162e6 * 2 * math.pi / u.s))
print "Aluminum skin depth at 162 MHz is " + str(delta_func(2.82e-8 * u.ohm * u.m, 162e6 * 2 * math.pi / u.s))
print "Water resistance at 162 MHz is " + str(R_water([162e6])[0]) + " Ohms"
print "Aluminum resistance at 162 MHz is " + str(R_aluminum([162e6])[0]) + " Ohms"

fstart, fend, fsteps = 1., 10e9, 50
freq_points = indep_array(fstart, fend, fsteps)
R_water = R_water(freq_points)
R_alum = R_aluminum(freq_points)

plt.plot(freq_points, R_water, '-', label = 'water', linewidth = 4)
plt.plot(freq_points, R_alum, '--', label = 'aluminum', linewidth = 4)
plt.vlines(162e6, 0, 1e7, linestyle = '--')
plt.yscale('log')
plt.xscale('log')
plt.xlabel('Frequency (s$^{-1}$)')
plt.ylabel('Re(Z) ($\Omega$)')
plt.legend(loc = 'best')
plt.savefig('/home/lindsayad/gdrive/Pictures/alum_vs_water_propagation.eps', format = 'eps')
plt.show()
