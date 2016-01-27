from paraview.simple import *
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from collections import OrderedDict
from matplotlib import rc
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})
N_A = 6.02e23
coulomb = 1.6e-19

path = "/home/lindsayad/gdrive/MooseOutput/"
pic_path = "/home/lindsayad/gdrive/Pictures/"
PIC = False
save = False
mode = "thermo"

if mode == "kinetic":
    # Files for kinetic plots
    file_root = "mean_en_kinetic_r_0"
    job_names = ["_no_salt_or_H3Op", "pt9_no_salt_or_H3Op", "pt99_no_salt_or_H3Op", "pt999_no_salt_or_H3Op", "pt9999_no_salt_or_H3Op"]
    short_names = ["$\gamma=1$", "$\gamma=10^{-1}$", "$\gamma=10^{-2}$", "$\gamma=10^{-3}$", "$\gamma=10^{-4}$"]

elif mode == "energybc":
    # Files for energy bc plot. Comparison of energy BCs for H = 1
    file_root = "mean_en_thermo_no_salt_or_H3Op_H_1"
    job_names = ["_Hagelaar_energy", "_zero_grad_mean_en"]
    short_names = ["vacuum", "zero grad"]

elif mode == "thermo":
    # Files for thermo plot. Comparison of different values of H
    file_root = "mean_en_thermo_no_salt_or_H3Op_H_"
    suffix = "_zero_grad_mean_en"
    job_names = ["1", "10", "100", "1000", "10000", "100000"]
    short_names = ["H = 1", "H = 1e1", "H = 1e2", "H = 1e3", "H = 1e4", "H = 1e5"]
    job_names = [job + suffix for job in job_names]

name_dict = {x:y for x,y in zip(job_names, short_names)}
xtickers = [0, .25e-3, .5e-3, .75e-3, 1e-3]
xticker_labels = ['0','250', '500', '750', '1000']

data = OrderedDict()
cellData = OrderedDict()
cellGasData = OrderedDict()
cellLiquidData = OrderedDict()
pointGasData = OrderedDict()
pointLiquidData = OrderedDict()
index = 0
GasElemMax = 0
for job in job_names:
    file_sans_ext = path + file_root + job + "_gold_out"
    inp = file_sans_ext + ".e"
    out = file_sans_ext + ".csv"

    reader = ExodusIIReader(FileName=inp)
    tsteps = reader.TimestepValues
    writer = CreateWriter(out, reader)
    writer.Precision = 16
    writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
    del writer

    for i in range(2,6):
        os.remove(file_sans_ext + str(i) + ".csv")

    new_inp0 = file_sans_ext + "0.csv"
    data[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
    pointGasData[job] = data[job]

    # Use for coupled gas-liquid simulations
    new_inp1 = file_sans_ext + "1.csv"
    data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
    pointLiquidData[job] = data1
    data[job] = np.concatenate((data[job],data1), axis=0)

    writer = CreateWriter(out, reader)
    writer.FieldAssociation = "Cells"
    writer.Precision = 16
    writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
    del writer

    for i in range(2,6):
        os.remove(file_sans_ext + str(i) + ".csv")

    new_inp0 = file_sans_ext + "0.csv"
    cellData[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
    cellGasData[job] = cellData[job]
    if index == 0:
        GasElemMax = np.amax(cellData[job]['GlobalElementId'])

    # Use for coupled gas-liquid simulations
    new_inp1 = file_sans_ext + "1.csv"
    data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
    cellData[job] = np.concatenate((cellData[job],data1), axis=0)
    cellLiquidData[job] = data1

# # Emi data
# emi_path = "/home/lindsayad/gdrive/TabularData/emi_data/gas_only/"
# emi_x, emi_n_e = np.loadtxt(emi_path + "ne_vs_x.txt", unpack = True)
# emi_x, emi_n_i = np.loadtxt(emi_path + "ni_vs_x.txt", unpack = True)
# emi_x, emi_pot = np.loadtxt(emi_path + "Potential_vs_x.txt", unpack = True)
# emi_x, emi_efield = np.loadtxt(emi_path + "Efield_vs_x.txt", unpack = True)
# emi_x, emi_etemp = np.loadtxt(emi_path + "Te_vs_x.txt", unpack = True)

# plot_vars = ['potential']
# for var in plot_vars:
#     var_for_tex = var.replace("_"," ")
#     fig = plt.figure()
#     ax = fig.add_subplot(111)
#     for job in job_names:
#         job_for_tex = job.replace("_"," ")
#         ax.plot(data[job]['Points0'],data[job][var],label=name_dict[job], linewidth=2)
#     xmin = np.amin(data[job]['Points0'])
#     xmax = np.amax(data[job]['Points0'])
#     ax.set_xlabel('x (m)')
#     ax.set_ylabel(var_for_tex)
#     ax.set_xlim(-0.1 * (xmax - xmin) + xmin, 0.1 * (xmax - xmin) + xmax)
#     # ax.legend(loc='upper center',bbox_to_anchor=(0.5,1.1),fancybox=True,shadow=True,fontsize=12,ncol=len(data.keys())/2)
#     # fig.set_size_inches((10,9))
#     ax.legend(loc=0)
#     fig.tight_layout()
#     # fig.savefig('/home/lindsayad/Pictures/' + var + '_coupled.pdf',format='pdf')
# plt.show()

# cell_plot_vars = ['Arp_lin','em_lin']
# for var in cell_plot_vars:
#     var_for_tex = var.replace("_"," ")
#     fig = plt.figure()
#     ax = fig.add_subplot(111)
#     for job in job_names:
#         job_for_tex = job.replace("_"," ")
#         ax.plot(cellData[job]['x'],cellData[job][var],label=name_dict[job], linewidth=2)
#     xmin = np.amin(cellData[job]['x'])
#     xmax = np.amax(cellData[job]['x'])
#     ax.set_xlabel('x (m)')
#     ax.set_ylabel(var_for_tex)
#     ax.set_xlim(-0.1 * (xmax - xmin) + xmin, 0.1 * (xmax - xmin) + xmax)
#     ax.set_yscale('log')
#     # ax.legend(loc='upper center',bbox_to_anchor=(0.5,1.1),fancybox=True,shadow=True,fontsize=12,ncol=len(cellData.keys())/2)
#     # fig.set_size_inches((10,9))
#     ax.legend(loc=0)
#     fig.tight_layout()
#     fig.savefig('/home/lindsayad/Pictures/' + var + '_coupled.pdf',format='pdf')
# plt.show()

# # Plot of EField. Whole domain
# fig = plt.figure(figsize=(10., 5.), dpi = 80)
# plt.subplots_adjust(wspace=0.1)
# ax1 = plt.subplot(121)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Efield'], label = 'Efield gas', linewidth=2)
#     # ax1.set_ylim(0,7e18)
#     ax1.legend(loc=0)
#     ax1.set_xticks([0, .25e-3, .5e-3, .75e-3, 1e-3])
#     ax1.set_xticklabels(['0','250', '500', '750', '1000'])
#     ax1.set_xlabel('Distance from cathode (microns)')
#     ax1.set_ylabel('Electric field (kV/m)')
#     ax1.set_xlim(-.1e-3, 1.1e-3)
# ax2 = plt.subplot(122)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['Efield'], label = 'Efield liquid', linewidth=2)
#     ax2.legend(loc=0)
#     ax2.set_xticks([1e-3, 1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
#     ax2.set_xticklabels(['0', '25', '50', '75', '100'])
#     ax2.set_xlabel('Distance from interface (nm)')
#     ax2.yaxis.tick_right()
#     ax2.yaxis.set_label_position("right")
#     ax2.set_ylabel('Electric field (kV/m)')
#     ax2.set_xlim(1e-3 - 10e-9, 1e-3 + 100e-9 + 10e-9)
# # fig.tight_layout()
# fig.savefig('/home/lindsayad/Pictures/Efield_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/Efield_grad_Te_zero.eps', format='eps')
# plt.show()

# # Plot of potential. Whole domain
# fig = plt.figure(figsize=(12., 5.), dpi = 80)
# plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
# ax1 = plt.subplot(121)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['potential'], label = 'potential gas', linewidth=2)
#     ax1.set_ylim(-0.7,0)
#     ax1.set_xlim(0, 0.001)
#     ax1.legend(loc=0)
#     ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
#     ax1.set_xticklabels(['0','250', '500', '750'])
#     ax1.set_xlabel('Distance from cathode (microns)')
#     ax1.set_ylabel('Potential (kV)')
#     # fig.tight_layout()
#     # fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
# ax2 = plt.subplot(122)
# # ax2 = plt.subplot(122, sharey=ax1)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax2.plot(pointLiquidData[job]['Points0'], pointLiquidData[job]['potential'], label = 'potential liquid', linewidth=2)
#     ax2.legend(loc=0)
#     ax2.set_xticks([1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
#     ax2.set_xticklabels(['25', '50', '75', '100'])
#     ax2.set_xlabel('Distance from interface (nm)')
#     ax2.yaxis.tick_right()
#     ax2.yaxis.set_label_position("right")
#     ax2.set_ylabel('Potential (kV)')
#     # ax2.set_ylim(-0.7, 0)
# # fig.tight_layout()
# fig.savefig('/home/lindsayad/Pictures/potential_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/potential_grad_Te_zero.eps', format='eps')
# plt.show()

# # Plot of potential. Last bit of gas
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['potential'], label = 'potential gas', linewidth=2)
#     ax1.set_ylim(-0.05,0)
#     ax1.set_xlim(0.000999, 0.001)
#     ax1.legend(loc=0)
#     # ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
#     # ax1.set_xticklabels(['0','250', '500', '750'])
#     ax1.set_xlabel('Distance from cathode (microns)')
#     ax1.set_ylabel('Potential (kV)')
#     # fig.tight_layout()
#     # fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/potential_last_bit_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/potential_last_bit_grad_Te_zero.eps', format='eps')
# plt.show()

# Plot of electron densities. Whole gas-liquid domain
fig = plt.figure(figsize=(10., 5.), dpi = 80)
plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
ax1 = plt.subplot(121)
for job in job_names:
    ax1.plot(cellGasData[job]['x'], cellGasData[job]['em_lin'], label = name_dict[job], linewidth=2)
ax1.set_yscale('log')
ax1.legend(loc='upper left', fontsize = 16)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode ($\mu m$)')
ax1.set_ylabel('Gas Electron Density (m$^{-3}$)')
ax2 = plt.subplot(122)
for job in job_names:
    ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['emliq_lin'], label = name_dict[job], linewidth=2)
ax2.legend(loc=0, fontsize = 16)
ax2.set_xticks([1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
ax2.set_xticklabels(['25', '50', '75', '100'])
ax2.set_xlabel('Distance from interface ($nm$)')
ax2.yaxis.tick_right()
ax2.yaxis.set_label_position("right")
ax2.set_ylabel('Liquid Electron Density (m$^{-3}$)')
ax2.set_yscale('log')
if save:
    if mode == "kinetic":
        fig.savefig('/home/lindsayad/Pictures/plasliq_electron_density_full_kinetic.eps', format='eps')
    elif mode == "energybc":
        fig.savefig('/home/lindsayad/Pictures/plasliq_electron_density_full_energy_bc.eps', format='eps')
    elif mode == "thermo":
        fig.savefig(pic_path + "plasliq_electron_density_full_thermo.eps", format='eps')
plt.show()

# Plot of ion density. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    ax1.plot(cellGasData[job]['x'], cellGasData[job]['Arp_lin'], label = name_dict[job], linewidth=2)
ax1.legend(loc='best', fontsize = 16)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode ($\mu m$)')
ax1.set_ylabel('Gas Ion Density (m$^{-3}$)')
if save:
    if mode == "kinetic":
        fig.savefig('/home/lindsayad/Pictures/plasliq_ion_density_full_kinetic.eps', format='eps')
    elif mode == "energybc":
        fig.savefig('/home/lindsayad/Pictures/plasliq_ion_density_full_energy_bc.eps', format='eps')
    elif mode == "thermo":
        fig.savefig(pic_path + "plasliq_ion_density_thermo.eps", format='eps')
plt.show()

# # Plot of ion densities. Whole gas domain
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Arp_lin'], label = name_dict[job], linewidth=2)
#     # ax1.set_ylim(0,7e19)
# ax1.set_xticks(xtickers)
# ax1.set_xticklabels(xticker_labels)
# ax1.set_xlabel('Distance from cathode (microns)')
# ax1.set_ylabel('Ion Density (m$^{-3}$)')
# # ax1.plot(emi_x, e mi_n_e, label = "PIC em", linewidth = 2)
# # ax1.plot(emi_x, emi_n_i, label = "PIC Arp", linewidth = 2)
# ax1.legend(loc=0)
# ax1.set_yscale('log')
# ax1.set_ylim(bottom=1e15)
# ax1.set_xlim(-.1e-3,1.1e-3)
# fig.savefig('/home/lindsayad/Pictures/gas_only_gamma_sweep_ions.eps', format='eps')
# plt.show()

# # Plot of electron densities. Whole gas domain
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['em_lin'], label = name_dict[job], linewidth=2)
# ax1.set_xticks(xtickers)
# ax1.set_xticklabels(xticker_labels)
# ax1.set_xlabel('Distance from cathode (microns)')
# ax1.set_ylabel('Electron Density (m$^{-3}$)')
# # ax1.plot(emi_x, e mi_n_e, label = "PIC em", linewidth = 2)
# # ax1.plot(emi_x, emi_n_i, label = "PIC Arp", linewidth = 2)
# ax1.legend(loc='upper left')
# ax1.set_yscale('log')
# ax1.set_xlim(-.1e-3,1.1e-3)
# fig.savefig('/home/lindsayad/Pictures/gas_only_gamma_sweep_electrons.eps', format='eps')
# plt.show()

# # Plot of densities. Last bit of gas phase
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['em_lin'], label = 'em_lin gas', linewidth=2)
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Arp_lin'], label = 'Arp_lin gas', linewidth=2)
#     # ax1.set_ylim(0,7e18)
#     ax1.set_xlim(0.00098, 0.001)
#     ax1.legend(loc=0)
#     ax1.set_xlabel('Distance from cathode (microns)')
#     ax1.set_ylabel('Density (m$^{-3}$)')
#     ax1.set_yscale('log')
# fig.savefig('/home/lindsayad/Pictures/densities_gas_interface_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/densities_gas_interface_grad_Te_zero.eps', format='eps')
# plt.show()

# Plot of potential. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['potential'], label = name_dict[job], linewidth=2)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Potential (kV)')
if PIC:
    ax1.plot(emi_x, emi_pot / 1000, label = "PIC pot", linewidth = 2)
ax1.legend(loc='best', fontsize = 16)
ax1.set_xlim(-.1e-3, 1.1e-3)
if save:
    if mode == "kinetic":
        fig.savefig(pic_path + "plasliq_potential_kinetic.eps", format = 'eps')
    elif mode == "energybc":
        fig.savefig('/home/lindsayad/Pictures/plasliq_potential_thermo_energy_bc.eps', format='eps')
    elif mode == "thermo":
        fig.savefig(pic_path + "plasliq_potential_thermo.eps", format='eps')
plt.show()

# # Plot of e fields. Whole gas domain
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Efield'], label = name_dict[job] + " E field", linewidth=2)
#     # ax1.set_ylim(0,7e19)
# ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
# ax1.set_xticklabels(['0','250', '500', '750'])
# ax1.set_xlabel('Distance from cathode (microns)')
# ax1.set_ylabel('Electric field (kV/m)')
# ax1.plot(emi_x, emi_efield / 1000, label = "PIC E field", linewidth = 2)
# ax1.legend(loc=0)
# fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_efield_compare.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_efield_compare.eps', format='eps')
# plt.show()

# Plot of e temp. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['e_temp'], label = name_dict[job], linewidth=2)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Electron temperature (V)')
if PIC:
    ax1.plot(emi_x, emi_etemp, label = "PIC em temp", linewidth = 2)
ax1.legend(loc='best', fontsize = 16)
ax1.set_xlim(-.1e-3, 1.1e-3)
if save:
    if mode == "kinetic":
        fig.savefig(pic_path + "plasliq_e_temp_kinetic.eps", format = 'eps')
    elif mode == "energybc":
        fig.savefig('/home/lindsayad/Pictures/plasliq_e_temp_thermo_energy_bc.eps', format='eps')
    elif mode == "thermo":
        fig.savefig(pic_path + "plasliq_e_temp_thermo.eps", format='eps')
plt.show()

# # Plot of fluxes. Whole domain
# fig = plt.figure(figsize=(10., 5.), dpi = 80)
# plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
# ax1 = plt.subplot(121)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['EFieldAdvAux_em'], label = 'Gas advective', linewidth=2)
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['DiffusiveFlux_em'], 'r-', label = 'Gas diffusive', linewidth=2)
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Current_em'] / -1.6e-19, 'g-', label = 'Gas total', linewidth=2)
#     ax1.set_ylim(-1e23,1e23)
#     ax1.legend(loc=0)
#     ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
#     ax1.set_xticklabels(['0','250', '500', '750'])
#     ax1.set_xlabel('Distance from cathode (microns)')
#     # ax1.set_ylabel('Density (m$^{-3}$) x 10$^{18}$')
#     # fig.tight_layout()
#     # fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
# ax2 = plt.subplot(122)
# # ax2 = plt.subplot(122, sharey=ax1)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['EFieldAdvAux_em'], label = 'Liquid advective', linewidth=2)
#     ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['DiffusiveFlux_em'], 'r-', label = 'Liquid diffusive', linewidth=2)
#     ax2.plot(cellLiquidData[job]['x'], cellLiquidData[job]['Current_em'] / -1.6e-19, 'g-', label = 'Liquid total', linewidth=2)
#     ax2.legend(loc=0)
#     ax2.set_xticks([1e-3 + 25e-9, 1e-3 + 50e-9, 1e-3 + 75e-9, 1e-3 + 100e-9])
#     ax2.set_xticklabels(['25', '50', '75', '100'])
#     ax2.set_xlabel('Distance from interface (nm)')
#     ax2.yaxis.tick_right()
#     ax2.yaxis.set_label_position("right")
#     ax2.set_ylim(-1e23,1e23)
#     # ax2.set_ylabel('Density (m$^{-3}$) x 10$^{22}$')
# # fig.tight_layout()
# fig.savefig('/home/lindsayad/Pictures/fluxes_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/fluxes_grad_Te_zero.eps', format='eps')
# plt.show()

# # Plot of fluxes. Last bit of gas phase
# # fig = plt.figure(figsize=(10., 5.), dpi = 80)
# fig = plt.figure()
# # plt.subplots_adjust(wspace=0.00001, hspace = 0.00001)
# ax1 = fig.add_subplot(111)
# # ax1 = plt.subplot(121)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['EFieldAdvAux_em'], label = 'Gas advective', linewidth=2)
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['DiffusiveFlux_em'], 'r-', label = 'Gas diffusive', linewidth=2)
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Current_em'] / -1.6e-19, 'g-', label = 'Gas total', linewidth=2)
#     # ax1.set_ylim(-1e22,1e22)
#     ax1.set_xlim(0.000999, 0.001)
#     ax1.legend(loc=0)
#     # ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
#     # ax1.set_xticklabels(['0','250', '500', '750'])
#     ax1.set_xlabel('Distance from cathode (microns)')
#     # ax1.set_ylabel('Density (m$^{-3}$) x 10$^{18}$')
#     # fig.tight_layout()
#     # fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/fluxes_inset_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/fluxes_inset_grad_Te_zero.eps', format='eps')
# plt.show()

# # Plot of electron temperature
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['e_temp'], label = 'T_e gas', linewidth=2)
#     ax1.set_ylim(0, 6.0)
#     ax1.set_xlim(0, 0.001)
#     ax1.legend(loc=0)
#     ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
#     ax1.set_xticklabels(['0','250', '500', '750'])
#     ax1.set_xlabel('Distance from cathode (microns)')
#     ax1.set_ylabel('T_e (eV)')
# fig.savefig('/home/lindsayad/Pictures/e_temp_grad_Te_zero.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/e_temp_grad_Te_zero.eps', format='eps')
# plt.show()

# fig = plt.figure()
# ax = fig.add_subplot(111)
# TotElemMax = np.amax(cellData[job]['GlobalElementId'])
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax.plot(cellData[job]['GlobalElementId'][0:GasElemMax], cellData[job]['tot_gas_current'][0:GasElemMax], label = 'tot_gas_current ' + name_dict[job], linewidth=2)
#     ax.plot(cellData[job]['GlobalElementId'][GasElemMax:TotElemMax], cellData[job]['tot_liq_current'][GasElemMax:TotElemMax], label = 'tot_liq_current ' + name_dict[job], linewidth=2)
#     ax.set_xlim(-0.1 * TotElemMax, 1.1 * TotElemMax)
#     ax.legend(loc=(0.1,0.5))
#     ax.set_xlabel('Global element ID')
#     ax.set_ylabel('Current (Amps/m^2)')
#     fig.tight_layout()
#     fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
# plt.show()

# liquid_plot_vars = ['em_lin']
# for var in liquid_plot_vars:
#     var_for_tex = var.replace("_"," ")
#     fig = plt.figure()
#     ax = fig.add_subplot(111)
#     for job in job_names:
#         job_for_tex = job.replace("_"," ")
#         ax.plot(cellLiquidData[job]['x'],cellLiquidData[job][var],label=name_dict[job], linewidth=2)
#     xmin = np.amin(cellLiquidData[job]['x'])
#     xmax = np.amax(cellLiquidData[job]['x'])
#     ax.set_xlabel('x')
#     ax.set_ylabel(var_for_tex)
#     ax.set_xlim(-0.1 * (xmax - xmin) + xmin, 0.1 * (xmax - xmin) + xmax)
#     ax.set_yscale('log')
#     # ax.legend(loc='upper center',bbox_to_anchor=(0.5,1.1),fancybox=True,shadow=True,fontsize=12,ncol=len(cellLiquidData.keys())/2)
#     # fig.set_size_inches((10,9))
#     ax.legend(loc=0)
#     fig.tight_layout()
#     fig.savefig('/home/lindsayad/Pictures/' + var + '_coupled_liq_only_dummy.pdf',format='pdf')
# plt.show()
