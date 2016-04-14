from load_data import load_data
from plot_data import *
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from collections import OrderedDict
from matplotlib import rc
from matplotlib.ticker import ScalarFormatter
from test_module import hello_world
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})
nnN_A = 6.02e23
coulomb = 1.6e-19

path = "/home/lindsayad/gdrive/MooseOutput/"
pic_path = "/home/lindsayad/gdrive/Pictures/"
cellGasData = OrderedDict()
cellLiquidData = OrderedDict()
pointGasData = OrderedDict()
pointLiquidData = OrderedDict()

# Emi data
emi_path = "/home/lindsayad/gdrive/TabularData/emi_data/gas_only/"
emi_x, emi_n_e = np.loadtxt(emi_path + "ne_vs_x.txt", unpack = True)
emi_x, emi_n_i = np.loadtxt(emi_path + "ni_vs_x.txt", unpack = True)
emi_x, emi_pot = np.loadtxt(emi_path + "Potential_vs_x.txt", unpack = True)
emi_x, emi_efield = np.loadtxt(emi_path + "Efield_vs_x.txt", unpack = True)
emi_x, emi_etemp = np.loadtxt(emi_path + "Te_vs_x.txt", unpack = True)

PIC = False
global_save = True
pos_scaling = 1
left_start = 0
# microns = (1e-3 - left_start) * 1e6
# mic_step = microns / 5
microns = 1000
mic_step = 200
# ticks = [left_start + i * 1e-6 for i in range(0, int(microns + mic_step), int(mic_step))]
# ticklabels = ['{:.2e}'.format(tick) for tick in ticks]
ticks = [1e-3 - i * 1e-6 for i in range(microns, -mic_step, -mic_step)]
ticklabels = [str(microns - i) for i in range(0, microns + mic_step, mic_step)]
xmin = 1e-3 - 1.1 * microns * 1e-6
xmax = 1e-3 + .1 * microns * 1e-6
ymin = -.2e22
ymax = 1.1e22

job_names = ['', 'pt9', 'pt99', 'pt999', 'pt9999']
# job_names = ["_r_en_0", "pt9999_r_en_0"]
# job_names = ['', 'e1', 'e2', 'e3', 'e4', 'e5', 'e6', 'e7']
# job_names = ['', '_low_resist']
# job_names = ['15', '3', 'ZeroFive']
# job_names = ['mean_en_r_dens_0' + i + '_r_en_0' for i in job_names]
# job_names = ['mean_en_r_dens_0pt9999_r_en_0' + i for i in job_names]
job_names = ['mean_en_r_dens_0pt99_r_en_0' + i for i in job_names]
# job_names = ['mean_en_H_1' + i + '_r_en_0' for i in job_names]
# job_names = ['mean_en_se_coeff_pt' + i for i in job_names]

# short_names = ["$\gamma_{dens}=1$", "$\gamma_{dens}=10^{-1}$", "$\gamma_{dens}=10^{-2}$", "$\gamma_{dens}=10^{-3}$", "$\gamma_{dens}=10^{-4}$"]
short_names = ["$\gamma_{en}=1$", "$\gamma_{en}=10^{-1}$", "$\gamma_{en}=10^{-2}$", "$\gamma_{en}=10^{-3}$", "$\gamma_{en}=10^{-4}$"]
# short_names = ["$\gamma_{dens}=1$", "$\gamma_{dens}=10^{-4}$"]
# short_names = ['$R = 10^6\Omega$', '$R = 8.1\cdot10^3\Omega$']
# short_names = ["$H=1$", "$H=10^2$", "$H=10^4$", "$H=10^6$"]
# short_names = ["$\gamma_p=.15$", "$\gamma_p=.30$", "$\gamma_p=.05$"]

num_jobs = len(job_names)

labels_list = ['blue', 'red', 'green', 'orange', 'magenta']
styles_list = ['solid', 'dashed', 'dashdot']
labels = [labels_list[i] for i in range(num_jobs)]
mesh_struct = ["scaled" for i in range(num_jobs)]
styles = [styles_list[i % 3] for i in range(num_jobs)]
job_colors = labels
job_color_dict = {x:y for x,y in zip(job_names, job_colors)}
name_dict = {x:y for x,y in zip(job_names, short_names)}

gas_variables = ['tot_gas_current']
# gas_var_labels = ['; e$^-$', '; Ar$^+$']
gas_var_labels = ['; el', '; ex', '; iz']
num_gas_vars = len(gas_variables)
gas_var_styles = [styles_list[i % 3] for i in range(num_gas_vars)]
gas_var_label_dict = {x:y for x,y in zip(gas_variables, gas_var_labels)}
gas_var_style_dict = {x:y for x,y in zip(gas_variables, gas_var_styles)}
liquid_variables = ['emliq_lin']
liq_var_labels = ['; e$^-$', '; OH$^-$']
num_liq_vars = len(liquid_variables)
liq_var_styles = [styles_list[i % 3] for i in range(num_liq_vars)]
liq_var_label_dict = {x:y for x,y in zip(liquid_variables, liq_var_labels)}
liq_var_style_dict = {x:y for x,y in zip(liquid_variables, liq_var_styles)}

y_axis_dict = {'e_temp' : 'Electron temperature (V)', 'em_lin' : 'Electron density (m$^{-3}$)', 'Arp_lin' : 'Ion density (m$^{-3}$)', 'Efield' : 'Electric field (V/m)', 'potential' : 'Potential (kV)', 'ProcRate_iz' : 'Rate of ionization (\# $m^{-3}$ $s^{-1}$)', 'tot_gas_current' : 'Current (A m$^{-2}$)'}
indep_var_dict = {'e_temp' : 'Points0', 'em_lin' : 'x', 'Arp_lin' : 'x', 'Efield' : 'x', 'potential' : 'Points0', 'ProcRate_iz' : 'x', 'tot_gas_current' : 'x'}

cellGasData, cellLiquidData, pointGasData, pointLiquidData = load_data(job_names, short_names, labels, mesh_struct, styles)
# pointGasData, pointLiquidData = load_data(job_names, short_names, labels, mesh_struct, styles, point_only=True)

for job in job_names:
    pointGasData[job]['Points0'] = 1e-3 * pointGasData[job]['Points0']
#     cellGasData[job]['tot_gas_current'] = -cellGasData[job]['tot_gas_current']
data_dict = {'e_temp' : pointGasData, 'em_lin' : cellGasData, 'Arp_lin' : cellGasData, 'Efield' : cellGasData, 'potential' : pointGasData, 'ProcRate_iz' : cellGasData, 'tot_gas_current' : cellGasData}

cell_gas_generic(data_dict[gas_variables[0]], job_names, name_dict, gas_variables, 'Distance from Interface ($\mu$m)', y_axis_dict[gas_variables[0]], save = True, tight_plot = True, show_plot = False, job_colors = job_color_dict, var_styles = gas_var_style_dict, var_labels = gas_var_label_dict, save_string = 'Dummy', x1min = xmin, x1max = xmax, x1ticks = ticks, x1ticklabels = ticklabels, indep_var = indep_var_dict[gas_variables[0]])#, y1max = .2e26, y1min=0)#, yscale = 'log')
# cell_coupled_generic(cellGasData, cellLiquidData, job_names, name_dict, gas_variables, liquid_variables, 'Distance from Interface ($\mu$m)', 'Liquid coordinate (m)', 'Electron Gas Density (\# m$^{-3}$)', 'Liquid Electron Density (\# m$^{-3}$)', save = True, tight_plot = False, show_plot = False, job_colors = job_color_dict, var_styles = gas_var_style_dict, var_labels = gas_var_label_dict, liq_var_styles = liq_var_style_dict, liq_var_labels = liq_var_label_dict, save_string = 'Dummy', yscale = 'log', x1ticks = ticks, x1ticklabels = ticklabels)# y1min = 1e17, y2min = 1e21, y1max = 1e19, y2max = 1e23, x1min = -.05e-3, x1max = 1.05e-3, x2min = 0.9e-7, x2max = 2.1e-7)#, )
