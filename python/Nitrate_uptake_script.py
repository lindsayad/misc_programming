#!/usr/bin/python
#
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
#
mpl.rcParams.update({'font.size': 16})
#
arrowShrinkSize = 0.1
#figureFontSize = 12
arrowWidth = 1
N_A = 6.02e23
#
time, NitrateConvection = np.loadtxt('Nitrate_uptake_convection_included.txt',unpack = True)
time_min, time_max = time.min(), time.max()
#Surface_min, Surface_max = H2OSurface.min(), H2OSurface.max()
#
time2, NitrateDiffusion = np.loadtxt('Nitrate_uptake_convection_not_included.txt',unpack = True)
time2_min, time2_max = time2.min(), time2.max()
#Half_min, Half_max = H2OHalf.min(), H2OHalf.max()
#
Convection = plt.plot(time,NitrateConvection, 'k-', label = 'w/ convection')
Diffusion = plt.plot(time2,NitrateDiffusion, 'k--', label = 'w/o convection')
#plt.xlabel('Time (s)', fontsize = figureFontSize)
plt.xlabel('Time (s)')
#plt.ylabel('Volume-averaged nitrate concentration (mmol/L)', fontsize = figureFontSize)
plt.ylabel('Volume-averaged nitrate concentration (mmol/L)')
plt.legend(loc=4)
plt.ticklabel_format(style='sci')
plt.gcf().tight_layout()
plt.savefig('Nitrate_uptake_plot.eps',format='eps')
plt.show()
