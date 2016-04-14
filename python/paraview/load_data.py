from collections import OrderedDict
from paraview.simple import *
import os
import numpy as np

def load_data(job_names, short_names, labels, mesh_struct, styles, point_only=False):
    data = OrderedDict()
    cellData = OrderedDict()
    cellGasData = OrderedDict()
    cellLiquidData = OrderedDict()
    pointGasData = OrderedDict()
    pointLiquidData = OrderedDict()

    index = 0
    GasElemMax = 0
    path = "/home/lindsayad/gdrive/MooseOutput/"
    for job in job_names:
        file_sans_ext = path + job + "_gold_out"
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

        # Use for coupled gas-liquid simulations
        new_inp1 = file_sans_ext + "1.csv"
        data1 = np.genfromtxt(new_inp1, delimiter=',', names=True)
        pointLiquidData[job] = data1
        data[job] = np.concatenate((data[job],data1), axis=0)

        if not point_only:

            writer = CreateWriter(out, reader)
            writer.FieldAssociation = "Cells"
            writer.Precision = 16
            writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
            del writer

            # for i in range(0,10):
            #     os.remove(file_sans_ext + str(i) + ".csv")

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

    if not point_only:
        return cellGasData, cellLiquidData, pointGasData, pointLiquidData

    return pointGasData, pointLiquidData
