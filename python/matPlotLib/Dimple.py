#!/usr/bin/python
#
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
#
mpl.rcParams.update({'font.size': 16})
from matplotlib import rc
rc('text', usetex=True)
#
arrowShrinkSize = 0.1
figureFontSize = 16
arrowWidth = 1
N_A = 6.02e23
#
time, NOnoDimple, NOyesDimple = np.loadtxt('Dimple_comparison.txt',unpack = True)
time_min, time_max = time.min(), time.max()
#
ax = plt.subplot(111)
noDimple = plt.plot(time,NOnoDimple, 'k-', label = 'w/o depression')
Dimple = plt.plot(time,NOyesDimple, 'k--', label = 'w/ depression')
plt.xlabel('Time (s)', fontsize = figureFontSize)
plt.ylabel('moles NO in aqueous phase (moles)', fontsize = figureFontSize)
plt.legend(loc=4, fontsize = figureFontSize)
#
xlabel = ax.xaxis.set_tick_params(labelsize = figureFontSize)
ylabel = ax.yaxis.set_tick_params(labelsize = figureFontSize)
ax.ticklabel_format(style='sci')
#
plt.savefig('NO_dimple_plot.eps',format='eps')
plt.show()
