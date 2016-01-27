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


zipped = zip(cellGasData[mean_en_job_name]['x'],cellGasData[mean_en_job_name]['Efield'])
x = cellGasData[mean_en_job_name]['x']
Efield = cellGasData[mean_en_job_name]['Efield']
dx = np.zeros(x.size - 1)
dEfield = np.zeros(Efield.size - 1)
lambdaE = np.zeros(Efield.size - 1)
for i in range(len(lambdaE)):
    lambdaE[i] = abs(Efield[i]) / abs((Efield[i] - Efield[i+1]) / (x[i] - x[i+1]))
plt.plot(x[0:len(x)-1], lambdaE)
plt.yscale('log')
plt.savefig('/home/lindsayad/Pictures/length_scale_of_efield_variation.eps', format='eps')
plt.show()

# np.savetxt('z.csv',zipped, fmt='%e,%e')
