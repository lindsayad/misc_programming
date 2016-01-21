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
file_root = ""
LFA_job_name = "LFA_just_plasma_1e6_resist_solved_to_DC"
mean_en_job_name = "mean_en_just_plasma_full_hagelaar_bcs_1e6_resist_gamma_pt15_interp_trans_advanced_voltage_bc_no_adv_stabiliz_DC"
job_names = [LFA_job_name, mean_en_job_name]
LFA_short = "LFA"
mean_en_short = "EEE"
short_names = [LFA_short, mean_en_short]
style_list = ['g-', 'b--']
name_dict = {x:y for x,y in zip(job_names, short_names)}
style_dict = {x:y for x, y in zip(job_names, style_list)}
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

    # for i in range(2,6):
    #     os.remove(file_sans_ext + str(i) + ".csv")

    new_inp0 = file_sans_ext + "0.csv"
    data[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
    pointGasData[job] = data[job]

    # # Use for coupled gas-liquid simulations
    # new_inp1 = file_sans_ext + "1.csv"
    # data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
    # pointLiquidData[job] = data1
    # data[job] = np.concatenate((data[job],data1), axis=0)

    writer = CreateWriter(out, reader)
    writer.FieldAssociation = "Cells"
    writer.Precision = 16
    writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
    del writer

    # for i in range(2,6):
    #     os.remove(file_sans_ext + str(i) + ".csv")

    new_inp0 = file_sans_ext + "0.csv"
    cellData[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
    cellGasData[job] = cellData[job]
    if index == 0:
        GasElemMax = np.amax(cellData[job]['GlobalElementId'])

    # # Use for coupled gas-liquid simulations
    # new_inp1 = file_sans_ext + "1.csv"
    # data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
    # cellData[job] = np.concatenate((cellData[job],data1), axis=0)
    # cellLiquidData[job] = data1

# Emi data
emi_path = "/home/lindsayad/gdrive/TabularData/emi_data/gas_only/"
emi_x, emi_n_e = np.loadtxt(emi_path + "ne_vs_x.txt", unpack = True)
emi_x, emi_n_i = np.loadtxt(emi_path + "ni_vs_x.txt", unpack = True)
emi_x, emi_pot = np.loadtxt(emi_path + "Potential_vs_x.txt", unpack = True)
emi_x, emi_efield = np.loadtxt(emi_path + "Efield_vs_x.txt", unpack = True)
emi_x, emi_etemp = np.loadtxt(emi_path + "Te_vs_x.txt", unpack = True)

# # Plot of densities. Whole gas domain
# fig = plt.figure()
# ax1 = plt.subplot(111)
# for job in job_names:
#     job_for_tex = job.replace("_"," ")
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['em_lin'], label = name_dict[job] + " em", linewidth=2)
#     ax1.plot(cellGasData[job]['x'], cellGasData[job]['Arp_lin'], label = name_dict[job] + " Arp", linewidth=2)
#     # ax1.set_ylim(0,7e19)
# ax1.set_xticks([0, .25e-3, .5e-3, .75e-3])
# ax1.set_xticklabels(['0','250', '500', '750'])
# ax1.set_xlabel('Distance from cathode (microns)')
# ax1.set_ylabel('Densities (m$^{-3}$)')
# ax1.plot(emi_x, emi_n_e, label = "PIC em", linewidth = 2)
# ax1.plot(emi_x, emi_n_i, label = "PIC Arp", linewidth = 2)
# ax1.legend(loc=0)
# fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_densities_compare.pdf', format='pdf')
# fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_densities_compare.eps', format='eps')
# plt.show()

# Plot of ion density. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    job_for_tex = job.replace("_"," ")
    ax1.plot(cellGasData[job]['x'], cellGasData[job]['Arp_lin'], style_dict[job], label = name_dict[job], linewidth=2)
    # ax1.set_ylim(0,7e19)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Ion density (m$^{-3}$)')
ax1.plot(emi_x, emi_n_i, 'r-.', label = "PIC", linewidth = 2)
ax1.legend(loc=0)
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_ion_density_compare.pdf', format='pdf')
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_ion_density_compare.eps', format='eps')
plt.show()

# Plot of electron density. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    job_for_tex = job.replace("_"," ")
    ax1.plot(cellGasData[job]['x'], cellGasData[job]['em_lin'], style_dict[job], label = name_dict[job], linewidth=2)
    # ax1.set_ylim(0,7e19)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Electron density (m$^{-3}$)')
ax1.plot(emi_x, emi_n_e, 'r-.', label = "PIC", linewidth = 2)
ax1.legend(loc=0)
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_electron_density_compare.pdf', format='pdf')
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_electron_density_compare.eps', format='eps')
plt.show()

# Plot of potential. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    job_for_tex = job.replace("_"," ")
    ax1.plot(pointGasData[job]['Points0'], pointGasData[job]['potential'], style_dict[job], label = name_dict[job], linewidth=2)
    # ax1.set_ylim(0,7e19)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Potential (kV)')
ax1.plot(emi_x, emi_pot / 1000, 'r-.', label = "PIC", linewidth = 2)
ax1.legend(loc=0)
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_potential_compare.pdf', format='pdf')
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_potential_compare.eps', format='eps')
plt.show()

# Plot of e fields. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
for job in job_names:
    job_for_tex = job.replace("_"," ")
    ax1.plot(cellGasData[job]['x'], cellGasData[job]['Efield'], style_dict[job], label = name_dict[job], linewidth=2)
    # ax1.set_ylim(0,7e19)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Electric field (kV/m)')
ax1.plot(emi_x, emi_efield / 1000, 'r-.', label = "PIC", linewidth = 2)
ax1.legend(loc=0)
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_efield_compare.pdf', format='pdf')
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_efield_compare.eps', format='eps')
plt.show()

# Plot of e temp. Whole gas domain
fig = plt.figure()
ax1 = plt.subplot(111)
ax1.plot(pointGasData[job]['Points0'], pointGasData[mean_en_job_name]['e_temp'], 'b--', label = "EEE", linewidth=2)
ax1.set_xticks(xtickers)
ax1.set_xticklabels(xticker_labels)
ax1.set_xlabel('Distance from cathode (microns)')
ax1.set_ylabel('Electron temperature (V)')
ax1.plot(emi_x, emi_etemp, 'r-.', label = "PIC", linewidth = 2)
ax1.legend(loc=0)
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_etemp_compare.pdf', format='pdf')
fig.savefig('/home/lindsayad/Pictures/LFA_mean_en_etemp_compare.eps', format='eps')
plt.show()
