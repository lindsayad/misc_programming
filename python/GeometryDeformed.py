#!/usr/bin/python
#
# To-do list: Adapt this to plot the HNO3Convection vapor data
#
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import matplotlib.patches as mpatches
#
dpiRatio = 300.0/80.0
DishRadius = 0.03
WaterHeight = 0.0035368
GapDistance = 0.0064632
NeedleRadius = .00062
arrowShrinkSize = 0.1
figureFontSize = 12
arrowWidth = 1
#
'''HNO3DiffusionData = np.loadtxt('HNO3_convection.txt')
i = 0
a,b = HNO3DiffusionData.shape
ainitial = a
while i < a:
    if np.isnan(HNO3DiffusionData[i,2]):
	    HNO3DiffusionData = np.delete(HNO3DiffusionData, (i), axis = 0)
	    a,b = HNO3DiffusionData.shape
    else:
        i = i + 1		
#
afinal = a
#
Nx1, idx1 = np.unique(HNO3DiffusionData[:,0], return_inverse=True)
Nx2, idx2 = np.unique(HNO3DiffusionData[:,1], return_inverse=True)
#
HNO3Diffusion = np.empty((Nx1.shape[0],Nx2.shape[0]))
HNO3Diffusion[idx1,idx2] = HNO3DiffusionData[:,2]
#
r, z = np.meshgrid(Nx1, Nx2)
#
HNO3Diffusion_min, HNO3Diffusion_max = np.min(HNO3Diffusion), np.max(HNO3Diffusion)
#
NO3mDiffusionData = np.loadtxt('NO3m_convection.txt')
i = 0
a,b = NO3mDiffusionData.shape
ainitial = a
while i < a:
    if np.isnan(NO3mDiffusionData[i,2]):
	    NO3mDiffusionData = np.delete(NO3mDiffusionData, (i), axis = 0)
	    a,b = NO3mDiffusionData.shape
    else:
        i = i + 1		
#
afinal = a
#
Nx1, idx1 = np.unique(NO3mDiffusionData[:,0], return_inverse=True)
Nx2, idx2 = np.unique(NO3mDiffusionData[:,1], return_inverse=True)
#
NO3mDiffusion = np.empty((Nx1.shape[0],Nx2.shape[0]))
NO3mDiffusion[idx1,idx2] = NO3mDiffusionData[:,2]
#
r2, z2 = np.meshgrid(Nx1, Nx2)
#
NO3mDiffusion_min, NO3mDiffusion_max = np.min(NO3mDiffusion), np.max(NO3mDiffusion)
#
fig = plt.figure(figsize=(6.5,5.0), dpi = 80)
ax = fig.add_subplot(111)
ax.set_aspect(1.0)
#
HNO3DiffusionAx = plt.pcolor(r, z, HNO3Diffusion.transpose(), cmap = 'gist_rainbow', vmin= 0, vmax = HNO3Diffusion_max)
HNO3DiffusionBar = plt.colorbar()
#HNO3DiffusionBar = plt.colorbar(ticks = [0.0, 1.0e16, 2.0e16, 3.0e16, 4.0e16, 5.0e16, 6.0e16, 7.0e16, 8.0e16])
HNO3DiffusionBar.set_label('Gaseous Nitric Acid Density (m^-3)')
#HNO3DiffusionBar.ax.set_yticklabels(['0.00','1.00','2.00','3.00','4.00','5.00','6.00','7.00','8.00'])
NO3mDiffusionAx = plt.pcolor(r2, z2, NO3mDiffusion.transpose(), cmap = 'gist_rainbow', vmin= 0, vmax = NO3mDiffusion_max)
NO3mDiffusionBar = plt.colorbar()
NO3mDiffusionBar.set_label('Aqueous Nitrate Density (m^-3)')'''
plt.axis([0.0,DishRadius+0.001,-WaterHeight,DishRadius-WaterHeight])
#
plt.xlabel('r (m)',fontsize = figureFontSize)
plt.ylabel('z (m)', fontsize = figureFontSize)
#
'''plt.annotate('Gas-liquid interface', xy=(0.017,0), xytext=(0.010,0.004),arrowprops=dict(facecolor='black',shrink=arrowShrinkSize, width = arrowWidth), fontsize = figureFontSize)
plt.annotate('Dish wall', xy=(DishRadius,0.002), xytext=(DishRadius-0.01, 0.01),arrowprops=dict(facecolor='black',shrink=arrowShrinkSize, width=arrowWidth), fontsize = figureFontSize)
#plt.annotate('Needle/jet outer wall',xy=(NeedleRadius+2.5e-4,0.02), xytext=(0.01,0.022), arrowprops=dict(facecolor='black',shrink=arrowShrinkSize, width = arrowWidth), fontsize = figureFontSize)
plt.annotate('Needle tip/jet outlet', xy = (NeedleRadius+2e-4,GapDistance), xytext = (0.005,0.015),arrowprops=dict(facecolor='black',shrink=arrowShrinkSize,width=arrowWidth), fontsize = figureFontSize)
plt.annotate('Symmetry axis', xy = (0,-0.002), xytext = (0.002,-WaterHeight/2-0.001),arrowprops=dict(facecolor='black',shrink=arrowShrinkSize,width=arrowWidth), fontsize = figureFontSize)'''
#
plt.annotate('Gas-liquid interface', xy=(0.012,0), xytext=(0,20), textcoords = 'offset points', ha = 'center', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Petri dish wall', xy=(DishRadius,0.002), xytext=(-20, 20), textcoords = 'offset points', ha = 'right', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#plt.annotate('Needle/jet outer wall',xy=(NeedleRadius+2.5e-4,0.02), xytext=(0.01,0.022), arrowprops=dict(facecolor='black',shrink=arrowShrinkSize, width = arrowWidth), fontsize = figureFontSize)
plt.annotate('Needle tip/jet outlet', xy = (NeedleRadius+2e-4,GapDistance), xytext = (20,20), textcoords = 'offset points', ha = 'left', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Symmetry axis', xy = (0,0.002), xytext = (20,20), textcoords = 'offset points', ha = 'left', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Flow development channel', xy = (0,0.017), xytext = (20,0), textcoords = 'offset points', ha = 'left', va = 'center', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Jet inlet', xy = (0,DishRadius-WaterHeight), xytext = (20,-20), textcoords = 'offset points', ha = 'left', va = 'top', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Interface deformation', xy = (0.00134,-0.000858), xytext = (10,-10), textcoords = 'offset points', ha = 'left', va = 'top', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#
plt.plot([DishRadius, DishRadius],[-WaterHeight,GapDistance], color='k', linestyle = '-', linewidth = 2)
plt.plot([NeedleRadius,NeedleRadius],[GapDistance,DishRadius-WaterHeight], color='k', linestyle = '-', linewidth = 2)
'''plt.plot([NeedleRadius+1e-4,NeedleRadius+1e-4],[GapDistance,DishRadius-WaterHeight], color='k', linestyle = '-', linewidth = 2)
plt.plot([NeedleRadius+2e-4,NeedleRadius+2e-4],[GapDistance,DishRadius-WaterHeight], color='k', linestyle = '-', linewidth = 2)'''
plt.plot([0.003625*np.sin(43.603*np.pi/180.0),DishRadius],[0,0], color='k', linestyle = '-', linewidth = 2) 
#
plt.text(0.020, 0.017, 'Gas phase', fontsize = figureFontSize)
plt.text(0.018, -0.0025, 'Liquid phase', fontsize = figureFontSize)
# 
myArc = mpatches.Arc((0,0.002625),0.00725,0.00725,270,0,43.603, linewidth = 2)
plt.gcf().gca().add_artist(myArc)
#
#fig.savefig('test.png',dpi=80)
plt.savefig('GeometryDeformed.eps',format='eps')
#
plt.show()


