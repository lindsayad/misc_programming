#!/usr/bin/python
#
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
#
mpl.rcParams.update({'font.size': 16})
#
arrowShrinkSize = 0.1
figureFontSize = 16
arrowWidth = 1
N_A = 6.02e23
#
time, NOConvection, NODiffusion = np.loadtxt('NO_uptake_convection_included_and_not_included.txt',unpack = True)
time_min, time_max = time.min(), time.max()
#
ax = plt.subplot(111)
Convection = plt.plot(time,NOConvection, 'k-', label = 'w/ convection')
Diffusion = plt.plot(time,NODiffusion, 'k--', label = 'w/o convection')
plt.xlabel('Time (s)', fontsize = figureFontSize)
plt.ylabel('Volume-averaged NO concentration (mmol/L)', fontsize = figureFontSize)
plt.legend(loc=4, fontsize = figureFontSize)
#ax.xaxis.label.set_fontsize(figureFontSize)
#ax.yaxis.label.set_fontsize(figureFontSize)
xlabel = ax.xaxis.set_tick_params(labelsize = figureFontSize)
ylabel = ax.yaxis.set_tick_params(labelsize = figureFontSize)
ax.ticklabel_format(style='sci')
#xlabel.set_fontsize(figureFontSize)
#ax.get_yticklabels().set_fontsize(figureFontSize)
#
plt.savefig('NO_uptake_plot.eps',format='eps')
plt.show()
