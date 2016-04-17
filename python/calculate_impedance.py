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

class byrn:
    d = .05 * u.m
    A = 9.6 * (u.cm)**2
    mu = 1e-2 * (u.m)**2 / (u.V * u.s)
    m = 9.11e-31 * u.kg
    T_g = 300 * u.K
    alpha = 2.1e-29 * (u.m)**3
    eps_r = 1.
    u.torr = u.mmHg
    def __init__(self, p):
        self.n_g = p * u.torr / (c.kB * self.T_g)
        self.nu_m = self.n_g * sqrt(math.pi * self.alpha * c.e**2 / (self.m * c.eps0))

class wtr:
    diff = 2e-9 * (u.m)**2 / u.s # reference Ranga
    T_l = 300 * u.K
    mu = diff * c.e / (c.kB * T_l)
    weight_Cl = 35.5 * u.g / u.mol
    m_Cl = weight_Cl / u.avogadro
    eps_r = 80.
    d = 1. * u.mm
    A = 9.6 * (u.cm)**2
    def __init__(self, conducting_ion):
        if conducting_ion == "Cl":
            self.m = self.m_Cl
        self.nu_m = c.e / (self.m * self.mu)

def impedance_arrays(dens_points, freq_points, params):
    Rp, Xp, Zp_mag = np.zeros((len(dens_points), len(freq_points))), np.zeros((len(dens_points), len(freq_points))), np.zeros((len(dens_points), len(freq_points)))
    for i in range(0, len(dens_points)):
        for j in range(0, len(freq_points)):
            eps, Yp, Zp = imp.impedance(freq_points[j] / u.s, params.m, dens_points[i] / (u.m)**3, params.A, params.d, params.eps_r, nu_m = params.nu_m)
            Rp[i][j] = re(Zp) / u.ohm
            Xp[i][j] = im(Zp) / u.ohm
            Zp_mag[i][j] = np.sqrt(Rp[i][j] ** 2 + Xp[i][j] ** 2)
    return Rp, Xp, Zp_mag

def plasma_imp_vs_pg(pg_points, freq, dens):
    Rp, Xp = np.zeros(len(pg_points)), np.zeros(len(pg_points))
    u.torr = u.mmHg
    for p,i in zip(pg_points, range(len(pg_points))):
        n_g = p * u.torr / (c.kB * byrn.T_g)
        nu_m = n_g * sqrt(math.pi * byrn.alpha * c.e**2 / (byrn.m * c.eps0))
        eps, Yp, Zp = imp.impedance(freq / u.s, byrn.m, dens / u.m ** 3, byrn.A, byrn.d, byrn.eps_r, nu_m = nu_m)
        Rp[i] = re(Zp) / u.ohm
        Xp[i] = im(Zp) / u.ohm
    return Rp, Xp

def imp_plot(indep_var, imp_var, imp_name, save_name, freq = True, labels = [''], styles = ['']):
    plt.close()
    for y_data, label, style in zip(imp_var, labels, styles):
        plt.plot(indep_var, y_data, label = label, linestyle = style, linewidth = 3)
    plt.yscale('log')
    plt.xscale('log')
    plt.ylabel(imp_name + ' ($\Omega$)')
    if freq is True:
        plt.xlabel('Frequency s$^{-1}$')
    else:
        plt.xlabel('Electron density (m$^{-3}$)')
    plt.legend(loc='best')
    plt.vlines(162e6, 0, 1e10, linestyle = '--')
    plt.savefig('/home/lindsayad/gdrive/Pictures/' + save_name + '.eps', format = 'eps')
    plt.show()

# pstart, pend, psteps = 1e-3, 760, 50
# p_pts = indep_array(pstart, pend, psteps)
# Rp, Xp = plasma_imp_vs_pg(p_pts, 162e6, 1e18)
# plt.plot(p_pts, np.abs(Xp))
# plt.xscale('log')
# plt.yscale('log')
# plt.xlabel('Gas pressure (torr)')
# plt.ylabel('Absolute value of the reactance ($\Omega$)')
# # plt.savefig('Reactance_mag_vs_pressure.eps', format = 'eps')
# plt.show()

freq_start, freq_end, freq_steps = 1, 10e9, 50
freq_points = indep_array(freq_start, freq_end, freq_steps)
atm_plas = byrn(760)
Rp_gas, Xp_gas, Zp_mag_gas = impedance_arrays([1e18], freq_points, atm_plas)

mass_conc_Cl = 13.3 * u.mg / u.l # reference Raleigh municipal plant
n_Cl = mass_conc_Cl / wtr.weight_Cl * u.avogadro
cl_soln = wtr("Cl")
Rp_liq, Xp_liq, Zp_mag_liq = impedance_arrays([n_Cl * u.m ** 3], freq_points, cl_soln)

# imp_plot(freq_points, Rp_gas[0,:], "resistance", "dummy")
# imp_plot(freq_points, -Xp_gas[0,:], "reactance magnitude", "freq_vs_reactance_ne_1e18")
# imp_plot(freq_points, Rp_liq[0,:], "Water resistance", "freq_vs_resistance_water")
# imp_plot(freq_points, -Xp_liq[0,:], "Water reactance", "freq_vs_reactance_water")
# imp_plot(freq_points, [Rp_gas[0,:], Rp_liq[0,:]], "Re(Z)", "Plasma_vs_water_resistance", labels = ['Plasma', 'Water'], styles = ['-', '--'])
# imp_plot(freq_points, [-Xp_gas[0,:], -Xp_liq[0,:]], '$|$Im(Z)$|$', "Plasma_vs_water_reactance", labels = ['Plasma', 'Water'], styles = ['-', '--'])
imp_plot(freq_points, [Zp_mag_gas[0,:], Zp_mag_liq[0,:]], '$|$Z$|$', "Plasma_vs_water_impedance_mag", labels = ['Plasma', 'Water'], styles = ['-', '--'])

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
