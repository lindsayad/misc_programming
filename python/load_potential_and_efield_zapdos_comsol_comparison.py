import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})

f = '/home/lindsayad/gdrive/MooseOutput/EField_and_potential.csv'
f_comsol = '/home/lindsayad/gdrive/MooseOutput/potential_and_efield.txt'

data = np.loadtxt(f,delimiter=',')
potential = data[:,0]
efield = -data[:,1]
arc_length = data[:,3]
comsol_data = np.loadtxt(f_comsol)
potential_comsol = comsol_data[:,1]
efield_comsol = comsol_data[:,2]
x_data = comsol_data[:,0]
x_data = x_data - 0.002
figPotential = plt.figure()
figEField = plt.figure()
axPotential = figPotential.add_subplot(111)
axEField = figEField.add_subplot(111)

axPotential.plot(arc_length,potential, 'g-', label='zapdos',linewidth=2)
axEField.plot(arc_length,efield, 'g-', label='zapdos',linewidth=2)#,'--')
axEField.plot(x_data,efield_comsol, 'b--', label='comsol',linewidth=2)#,'-.')
axPotential.plot(x_data,potential_comsol, 'b--', label='comsol',linewidth=2)#':',)
axPotential.set_xlabel('x (m)')
axPotential.set_ylabel('potential (V)')
axPotential.legend(loc=0)

axEField.set_xlabel('x (m)')
axEField.set_ylabel('Electric field (V/m)')
axEField.ticklabel_format(axis='y',style='sci',scilimits=(0,0))
axEField.legend(loc=0)

axEField.axvline(x=0,ymin=0,ymax=1,color='k',ls='--')
axEField.axvline(x=0.048,ymin=0,ymax=1,color='k',ls='--')
axEField.annotate('cathode', xy=(0.0385,0.5),xycoords='axes fraction',xytext=(0.08,0.55),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))
axEField.annotate('anode', xy=(0.9615,0.5),xycoords='axes fraction',xytext=(0.77,0.56),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))

axPotential.axvline(x=0,ymin=0,ymax=1,color='k',ls='--')
axPotential.axvline(x=0.048,ymin=0,ymax=1,color='k',ls='--')
axPotential.annotate('cathode', xy=(0.0385,0.5),xycoords='axes fraction',xytext=(0.08,0.55),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))
axPotential.annotate('anode', xy=(0.9615,0.5),xycoords='axes fraction',xytext=(0.77,0.56),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))

axEField.set_xlim([-.002,0.05])
axPotential.set_xlim([-.002,0.05])

figEField.tight_layout()
figPotential.tight_layout()

figPotential.savefig('/home/lindsayad/gdrive/Pictures/Potential.eps',format='eps')
figEField.savefig('/home/lindsayad/gdrive/Pictures/EField.eps',format='eps')

plt.show()
