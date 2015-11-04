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
TyrData = np.loadtxt('/home/alexlindsay/owncloudclient/Comsol_results/Text_files/Results/CarlyExpt/2D_tyr_conc.txt') 
i = 0
a,b = TyrData.shape
ainitial = a
while i < a:
    if np.isnan(TyrData[i,2]):
	    TyrData = np.delete(TyrData, (i), axis = 0)
	    a,b = TyrData.shape
    else:
        i = i + 1
#
afinal = a
#
Nx1, idx1 = np.unique(TyrData[:,0], return_inverse=True)
Nx2, idx2 = np.unique(TyrData[:,1], return_inverse=True)
#
Tyr = np.empty((Nx1.shape[0],Nx2.shape[0]))
Tyr[idx1,idx2] = TyrData[:,2]
#
r, z = np.meshgrid(Nx1, Nx2)
#
Tyr_min, Tyr_max = np.min(Tyr), np.max(Tyr)
#
surf = ax.plot_surface(r, z, Tyr.transpose(), rstride=1, cstride=1, cmap='jet', linewidth=0, antialiased=False, vmin = Tyr_min, vmax = Tyr_max) #, rasterized = True)
ax.set_zlim(Tyr_min, Tyr_max)
#
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.00f'))
ax.set_xlabel('r (m)')
ax.set_ylabel('z (m)')
ax.set_zlabel('[Tyr] (mol/m^3)')
ax.set_xticks([0.000,0.010,0.020,0.030])
ax.set_yticks([-0.003,-0.002,-0.001,0.000])
ax.set_xticklabels(['0.00','0.01','0.02','0.03'])
ax.set_yticklabels(['-0.003','-0.002','-0.001','0.000'])
ax.set_zticks([0.0003,0.0004,0.0005,0.0006])
ax.set_zticklabels(['3e-4','4e-4','5e-4','6e-4'])
#
TyrBar = fig.colorbar(surf, shrink = 0.5, aspect = 5)
TyrBar.set_label('[Tyr] (mol/m^3)')
TyrBar.set_ticks([0.0004,0.0005,0.0006])
TyrBar.set_ticklabels(['4e-4','5e-4','6e-4'])
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
# Default azim and elev for displaying the axes are azim = -60 and elev = 30 degrees
#
for ii in xrange(60,140,30):
    ax.view_init(elev=30., azim = ii)
    plt.gcf().tight_layout()
    fig.savefig("TyrNew"+str(ii)+".png",format='png')
#
#plt.show()
