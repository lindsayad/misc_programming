#!/usr/bin/python
#
# To-do list: Adapt this to plot the HNO3Convection vapor data
#
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import matplotlib.patches as mpatches
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
plt.annotate('Liquid container wall', xy=(DishRadius,0.002), xytext=(-20, 20), textcoords = 'offset points', ha = 'right', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Needle tip (positive high voltage)', xy = (NeedleRadius+2e-4,GapDistance), xytext = (20,20), textcoords = 'offset points', ha = 'left', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Symmetry axis', xy = (0,0.002), xytext = (20,20), textcoords = 'offset points', ha = 'left', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
plt.annotate('Ground', xy=(0.012,-WaterHeight), xytext=(0,20), textcoords = 'offset points', ha = 'center', va = 'bottom', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#plt.annotate('Flow development channel', xy = (0,0.017), xytext = (20,0), textcoords = 'offset points', ha = 'left', va = 'center', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#plt.annotate('Jet inlet', xy = (0,DishRadius-WaterHeight), xytext = (20,-20), textcoords = 'offset points', ha = 'left', va = 'top', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#plt.annotate('Interface deformation', xy = (0.00134,-0.000858), xytext = (10,-10), textcoords = 'offset points', ha = 'left', va = 'top', arrowprops=dict(facecolor='black', arrowstyle = '->'), fontsize = figureFontSize)
#
plt.plot([DishRadius, DishRadius],[-WaterHeight,GapDistance], color='k', linestyle = '-', linewidth = 2)
plt.plot([NeedleRadius,NeedleRadius],[GapDistance,DishRadius-WaterHeight], color='k', linestyle = '-', linewidth = 2)

plt.plot([0,DishRadius],[0,0], color='k', linestyle = '-', linewidth = 2) 
#
plt.text(0.020, 0.017, 'Gas phase', fontsize = figureFontSize)
plt.text(0.018, -0.0025, 'Liquid phase', fontsize = figureFontSize)
# 
# See http://matplotlib.org/api/patches_api.html for documentation of below command. 
# Some notes on the angles though: As stated in doc, angle rotates the ellipse angle 
# degrees counter-clockwise (in the direction consistent with angle measurements in 
# the unit circle). Theta 1 is the starting angle of the arc after rotation! E.g. 
# if the ellipse is rotated 90 degrees by the angle argument, then a value of 0 for
# theta1 means that the starting point of the arc drawing will be at the 90 degree
# position on the unit circle. Hopefully that makes sense
#
myArc = mpatches.Arc((0,GapDistance),2*NeedleRadius,4*NeedleRadius,0,270,360, linewidth = 2)
plt.gcf().gca().add_artist(myArc)
#
plt.savefig('GeometryForJannis.pdf',format='pdf')
#
plt.show()


