#!/usr/bin/python
#
from mpl_toolkits.mplot3d import Axes3D, proj3d
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl
#
mpl.rcParams.update({'font.size': 12})
#
arrowShrinkSize = 0.1
figureFontSize = 16
arrowWidth = 1
N_A = 6.02e23
#
fig = plt.figure()
ax = fig.gca(projection='3d')
logOHData = np.loadtxt('logOH_for_python.txt', dtype = complex) 
i = 0
a,b = logOHData.shape
ainitial = a
while i < a:
    if np.isnan(logOHData[i,2]):
	    logOHData = np.delete(logOHData, (i), axis = 0)
	    a,b = logOHData.shape
    else:
        i = i + 1
#
afinal = a
logOHData = logOHData.astype(float)
#
Nx1, idx1 = np.unique(logOHData[:,0], return_inverse=True)
Nx2, idx2 = np.unique(logOHData[:,1], return_inverse=True)
#
logOH = np.empty((Nx1.shape[0],Nx2.shape[0]))
logOH[idx1,idx2] = logOHData[:,2]
#
r, z = np.meshgrid(Nx1, Nx2)
#
logOH_min, logOH_max = np.min(logOH), np.max(logOH)
#
i = 0
a, b = logOH.shape
while i < b:
    j = 0
    while j < a:
        if logOH[j,i] < logOH[j-1,i]-1.0:
            logOH[j,i] = logOH[j-1,i]
        j = j + 1
    i = i + 1
#ax.set_aspect((z.max()-z.min())/(r.max()-r.min()))
surf = ax.plot_surface(r, z, logOH.transpose(), rstride=1, cstride=1, cmap='jet', linewidth=0, antialiased=False, vmin = -15.0, vmax = logOH_max) #, rasterized = True)
ax.plot_surface(-r, z, logOH.transpose(), rstride=1, cstride=1, cmap='jet', linewidth=0, antialiased=False, vmin = -15.0, vmax = logOH_max) #, rasterized = True)
ax.set_zlim(-15.0, logOH_max)
#
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.00f'))
ax.set_xlabel('r (m)')
ax.set_ylabel('z (m)')
ax.set_zlabel('log [OH(aq)]')
#ax.set_xticks([0.000,0.010,0.020,0.030])
ax.set_yticks([-0.003,-0.002,-0.001,0.000])
#ax.set_xticklabels(['0.00','0.01','0.02','0.03'])
ax.set_yticklabels(['0.003','-0.002','-0.001','0.000'])
#
OHBar = fig.colorbar(surf, shrink = 0.5, aspect = 5)
OHBar.set_label('log [OH(aq)]')
#
x2, y2, _ = proj3d.proj_transform(0,0,-6, ax.get_proj())
#
label = plt.annotate(
    "Stagnation point.", 
    xy = (x2, y2), xytext = (-20, -20),
	textcoords = 'offset points', ha = 'right', va = 'top',
    bbox = dict(boxstyle = 'round,pad=0.5', fc = 'yellow', alpha = 1.0),
    arrowprops = dict(arrowstyle = '->', connectionstyle = 'arc3,rad=0'))
#
#ax.set_aspect('equal')
#ax.plot([-r.max()],[z.min()],[-15.0],'w')
#ax.plot([r.max()],[z.min()],[-15.0],'w')
#ax.plot([-r.max()],[z.max()],[-15.0],'w')
#ax.plot([r.max()],[z.max()],[-15.0],'w')
#ax.plot([-r.max()],[z.min()],[-6.0],'w')
#ax.plot([r.max()],[z.min()],[-6.0],'w')
#ax.plot([-r.max()],[z.max()],[-6.0],'w')
#ax.plot([r.max()],[z.max()],[-6.0],'w')
#ax.view_init(30, -90) 
plt.gcf().tight_layout()
fig.savefig('logOH.png',format='png')
plt.show()
