from paraview.simple import *
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import OrderedDict

path = "/home/lindsayad/gdrive/MooseOutput/"
file_root = "LFA_"
job_names = ["lit_diff_mob_1e6_ballast_resist_no_H3Op_eps_80","simulated_out_to_dc_const_mob_diff_1e6_ballast_resist_no_art_diff_no_OHm_H3Op_eps_80","simulated_out_to_dc_const_mob_diff_1e6_ballast_resist_no_art_diff_no_OHm_H3Op_eps_one_restores_standard_density_shapes"]
short_names = ["trans-lit R-1e6 eps-80","trans-const R-1e6 eps-80","trans-const R-1e6 eps-1"]
name_dict = {x:y for x,y in zip(job_names, short_names)}

data = OrderedDict()
cellData = OrderedDict()
cellLiquidData = OrderedDict()
index = 0
GasElemMax = 0
for job in job_names:
    file_sans_ext = path + file_root + job + "_gold_out"
    inp = file_sans_ext + ".e"
    out = file_sans_ext + ".csv"

    reader = ExodusIIReader(FileName=inp)
    tsteps = reader.TimestepValues
    writer = CreateWriter(out, reader)
    writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
    del writer

    for i in range(2,6):
        os.remove(file_sans_ext + str(i) + ".csv")

    new_inp0 = file_sans_ext + "0.csv"
    data[job] = np.genfromtxt(new_inp0,delimiter=',', names=True)
    new_inp1 = file_sans_ext + "1.csv"
    data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
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
    if index == 0:
        GasElemMax = np.amax(cellData[job]['GlobalElementId'])
    new_inp1 = file_sans_ext + "1.csv"
    data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
    cellData[job] = np.concatenate((cellData[job],data1), axis=0)
    cellLiquidData[job] = data1

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
#     fig.savefig('/home/lindsayad/Pictures/' + var + '_coupled.pdf',format='pdf')
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

fig = plt.figure()
ax = fig.add_subplot(111)
TotElemMax = np.amax(cellData[job]['GlobalElementId'])
for job in job_names:
    job_for_tex = job.replace("_"," ")
    ax.plot(cellData[job]['GlobalElementId'][0:GasElemMax], cellData[job]['tot_gas_current'][0:GasElemMax], label = 'tot_gas_current ' + name_dict[job], linewidth=2)
    ax.plot(cellData[job]['GlobalElementId'][GasElemMax:TotElemMax], cellData[job]['tot_liq_current'][GasElemMax:TotElemMax], label = 'tot_liq_current ' + name_dict[job], linewidth=2)
    ax.set_xlim(-0.1 * TotElemMax, 1.1 * TotElemMax)
    ax.legend(loc=(0.1,0.5))
    ax.set_xlabel('Global element ID')
    ax.set_ylabel('Current (Amps/m^2)')
    fig.tight_layout()
    fig.savefig('/home/lindsayad/Pictures/current_continuity.pdf', format='pdf')
plt.show()

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
