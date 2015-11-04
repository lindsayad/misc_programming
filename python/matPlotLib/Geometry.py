#!/usr/bin/python
#
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
from matplotlib import rc
rc('text', usetex=True)
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
plt.axis([0.0,DishRadius+0.001,-WaterHeight,DishRadius-WaterHeight])
#
plt.xlabel('r (m)',fontsize = figureFontSize)
plt.ylabel('z (m)', fontsize = figureFontSize)
#
plt.annotate('Gas-liquid interface', xy=(0.012,0), xytext=(0,20), textcoords = 'offset points', ha = 'center', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Petri dish wall', xy=(DishRadius,0.002), xytext=(-20, 20), textcoords = 'offset points', ha = 'right', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Needle tip/jet outlet', xy = (NeedleRadius+2e-4,GapDistance), xytext = (20,20), textcoords = 'offset points', ha = 'left', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Symmetry axis', xy = (0,-0.002), xytext = (0.002,-WaterHeight/2-0.001),arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Flow development channel', xy = (0,0.017), xytext = (20,0), textcoords = 'offset points', ha = 'left', va = 'center', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Jet inlet', xy = (0,DishRadius-WaterHeight), xytext = (20,-20), textcoords = 'offset points', ha = 'left', va = 'top', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#
plt.plot([DishRadius, DishRadius],[-WaterHeight,GapDistance], color='k', linestyle = '-', linewidth = 2)
plt.plot([NeedleRadius,NeedleRadius],[GapDistance,DishRadius-WaterHeight], color='k', linestyle = '-', linewidth = 2)
plt.plot([0,DishRadius],[0,0], color='k', linestyle = '-', linewidth = 2) 
#
plt.text(0.020, 0.017, 'Gas phase', fontsize = figureFontSize)
plt.text(0.018, -0.0025, 'Liquid phase', fontsize = figureFontSize)
# 
plt.savefig('Geometry.eps',format='eps')
#
plt.show()


