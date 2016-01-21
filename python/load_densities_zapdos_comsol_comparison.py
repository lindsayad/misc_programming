import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
rc('text', usetex=True)

mpl.rcParams.update({'font.size': 20})

f = '/home/lindsayad/gdrive/MooseOutput/Ion_and_electron_densities_pared_down.csv'
f_comsol = '/home/lindsayad/gdrive/MooseOutput/Electron_and_ion_densities_comsol.txt'

data = np.loadtxt(f,delimiter=',')
ion_dens = data[:,0]
electron_dens = data[:,1]
arc_length = data[:,3]
comsol_data = np.loadtxt(f_comsol)
ion_dens_comsol = comsol_data[:,2]
electron_dens_comsol = comsol_data[:,1]
x_data = comsol_data[:,0]
x_data = x_data - 0.002
figIon_Dens = plt.figure()
figElectron_Dens = plt.figure()
axIon_Dens = figIon_Dens.add_subplot(111)
axElectron_Dens = figElectron_Dens.add_subplot(111)

axIon_Dens.plot(arc_length,ion_dens, 'g-', label='zapdos',linewidth=2)
axElectron_Dens.plot(arc_length,electron_dens, 'g-', label='zapdos',linewidth=2)#,'--')
axElectron_Dens.plot(x_data,electron_dens_comsol, 'b--', label='comsol',linewidth=2)#,'-.')
axIon_Dens.plot(x_data,ion_dens_comsol, 'b--', label='comsol',linewidth=2)#':',)
axIon_Dens.set_xlabel('x (m)')
axIon_Dens.set_ylabel('Ion density (m$^{-3}$)')
axIon_Dens.legend(loc=0)

axElectron_Dens.set_xlabel('x (m)')
axElectron_Dens.set_ylabel('Electron density (m$^{-3}$)')
axElectron_Dens.ticklabel_format(axis='y',style='sci',scilimits=(0,0))
axElectron_Dens.legend(loc=0)

axElectron_Dens.axvline(x=0,ymin=0,ymax=1,color='k',ls='--')
axElectron_Dens.axvline(x=0.048,ymin=0,ymax=1,color='k',ls='--')
axElectron_Dens.annotate('cathode', xy=(0.0385,0.5),xycoords='axes fraction',xytext=(0.08,0.55),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))
axElectron_Dens.annotate('anode', xy=(0.9615,0.5),xycoords='axes fraction',xytext=(0.77,0.56),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))

axIon_Dens.axvline(x=0,ymin=0,ymax=1,color='k',ls='--')
axIon_Dens.axvline(x=0.048,ymin=0,ymax=1,color='k',ls='--')
axIon_Dens.annotate('cathode', xy=(0.0385,0.5),xycoords='axes fraction',xytext=(0.08,0.55),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))
axIon_Dens.annotate('anode', xy=(0.9615,0.5),xycoords='axes fraction',xytext=(0.77,0.56),textcoords='axes fraction',arrowprops=dict(facecolor='black',shrink=0.1, width = 1))

axElectron_Dens.set_xlim([-.002,0.05])
axIon_Dens.set_xlim([-.002,0.05])

figElectron_Dens.tight_layout()
figIon_Dens.tight_layout()

figIon_Dens.savefig('/home/lindsayad/gdrive/Pictures/Ion_Dens.eps',format='eps')
figElectron_Dens.savefig('/home/lindsayad/gdrive/Pictures/Electron_Dens.eps',format='eps')

# plt.show()
