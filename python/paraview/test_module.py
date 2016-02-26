from collections import OrderedDict
import numpy as np

def hello_world(short_names, labels, mesh_struct, styles):
    global job_names, name_dict, cellGasData, cellLiquidData, pointGasData, pointLiquidData, label_dict, style_dict, mesh_dict
    data = OrderedDict()
    john = np.zeros(4)
    print short_names
