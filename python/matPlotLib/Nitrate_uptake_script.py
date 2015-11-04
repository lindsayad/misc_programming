#!/usr/bin/python
#
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
from matplotlib import rc
rc('text', usetex=True)
#
mpl.rcParams.update({'font.size': 16})
#
arrowShrinkSize = 0.1
arrowWidth = 1
N_A = 6.02e23
#
time, NitrateConvection = np.loadtxt('Nitrate_uptake_convection_included.txt',unpack = True)
time_min, time_max = time.min(), time.max()
time2, NitrateDiffusion = np.loadtxt('Nitrate_uptake_convection_not_included.txt',unpack = True)
time2_min, time2_max = time2.min(), time2.max()
Convection = plt.plot(time,NitrateConvection, 'k-', label = 'w/ convection')
Diffusion = plt.plot(time2,NitrateDiffusion, 'k--', label = 'w/o convection')
plt.xlabel('Time (s)')
plt.ylabel('Volume-averaged nitrate concentration (mmol/L)')
plt.legend(loc=4)
plt.ticklabel_format(style='sci')
plt.gcf().tight_layout()
plt.savefig('Nitrate_uptake_plot.eps',format='eps')
plt.show()
