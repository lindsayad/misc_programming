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
#logONOOHData = np.loadtxt('logONOOH_reduced_for_python.txt')
logONOOHData = np.loadtxt('log_ONOOH_reduced_for_python.txt', dtype = complex)  
i = 0
a,b = logONOOHData.shape
ainitial = a
while i < a:
    if np.isnan(logONOOHData[i,2]):
	    logONOOHData = np.delete(logONOOHData, (i), axis = 0)
	    a,b = logONOOHData.shape
    else:
        i = i + 1
#
amid1 = a
#
'''i = 0
while i < a:
    if np.iscomplex(logONOOHData[i,2]):
	    logONOOHData = np.delete(logONOOHData, (i), axis = 0)
	    a,b = logONOOHData.shape
    else:
        i = i + 1
#
amid2 = a
#
logONOOHData = logONOOHData.astype(float)
i = 0
while i < a:
    if logONOOHData[i,2] > -7.0:
	    logONOOHData = np.delete(logONOOHData, (i), axis = 0)
	    a,b = logONOOHData.shape
    else:
        i = i + 1
#
afinal = a'''
#
logONOOHData = logONOOHData.astype(float)
#
Nx1, idx1 = np.unique(logONOOHData[:,0], return_inverse=True)
Nx2, idx2 = np.unique(logONOOHData[:,1], return_inverse=True)
#
logONOOH = np.empty((Nx1.shape[0],Nx2.shape[0]))
logONOOH[idx1,idx2] = logONOOHData[:,2]
#
r, z = np.meshgrid(Nx1, Nx2)
#
logONOOH_min, logONOOH_max = np.min(logONOOH), np.max(logONOOH)
#
#ax.set_aspect((z.max()-z.min())/(r.max()-r.min()))
surf = ax.plot_surface(r, z, logONOOH.transpose(), rstride=1, cstride=1, cmap='jet', linewidth=0, antialiased=False) #, rasterized = True)
ax.set_zlim(logONOOH_min, logONOOH_max)
#
ax.zaxis.set_major_locator(LinearLocator(10))
#ax.zaxis.set_major_formatter(FormatStrFormatter('%.00f'))
ax.set_xlabel('r (m)')
ax.set_ylabel('z (m)')
ax.set_zlabel('log [ONOOH(aq)]')
ax.set_xticks([0.000,0.010,0.020,0.030])
ax.set_yticks([-0.003,-0.002,-0.001,0.000])
ax.set_xticklabels(['0.00','0.01','0.02','0.03'])
ax.set_yticklabels(['0.003','-0.002','-0.001','0.000'])
ax.set_zticks([-8.0,-9.0,-10.0,-11.0,-12.0,-13.0,-14.0,-15.0])
ax.set_zticklabels(['-8','-9','-10','-11','-12','-13','-14','-15'])
#
ONOOHBar = fig.colorbar(surf, shrink = 0.5, aspect = 5)
ONOOHBar.set_label('log [ONOOH(aq)]')
#
x2, y2, _ = proj3d.proj_transform(0,0,logONOOH_max-0.5, ax.get_proj())
#
label = plt.annotate(
    "Stagnation point.", 
    xy = (x2, y2), xytext = (-20, -20),
	textcoords = 'offset points', ha = 'right', va = 'top',
    bbox = dict(boxstyle = 'round,pad=0.5', fc = 'yellow', alpha = 1.0),
    arrowprops = dict(arrowstyle = '->'))
#
plt.gcf().tight_layout()
fig.savefig('logONOOH.png',format='png',transparent = False)
plt.show()
