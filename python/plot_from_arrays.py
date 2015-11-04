import numpy as np
import matplotlib.pyplot as plt
from collections import OrderedDict

plot_variables = ['elec','pion','phi','fld']
data = [var + '_dat' for var in plot_variables]
data = OrderedDict.fromkeys(data)
direc = '/home/lindsayad/gdrive/programming/usefulScripts/python/output/'
file_list = [direc + var + '.txt' for var in plot_variables]
for key, f in zip(data.keys(), file_list):
    data[key] = np.loadtxt(f, delimiter=', ')
a, b = data[data.keys()[0]].shape
figs = ['fig_' + var for var in plot_variables]
figs = OrderedDict.fromkeys(figs)
for key in figs.keys():
    figs[key] = plt.figure()
for fig, datum in zip(figs.keys(), data.keys()):
    ax = figs[fig].add_subplot(111)
    for i in range(1,a):
        ax.plot(data[datum][0,:],data[datum][i,:])
    figs[fig].suptitle(fig)
    print(fig)
    if (fig == 'fig_elec' or fig == 'fig_pion'):
        ax.set_yscale('log')
plt.show()
