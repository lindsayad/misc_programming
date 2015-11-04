import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
rc('text', usetex=True)
#
mpl.rcParams.update({'font.size': 16})

f = '/home/lindsayad/gdrive/MooseOutput/Ion_and_electron_densities_energy.csv'

data = np.loadtxt(f,delimiter=',')
ion_density = data[:,0]
electron_density = data[:,1]
arc_length = data[:,3]
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(arc_length,ion_density,label='zapdos ion density energy form',linewidth=2)
ax.plot(arc_length,electron_density,label='zapdos electron density energy form',linewidth=2)
ax.set_xlabel('x (m)')
ax.set_ylabel('densities (m$^{-3}$)')
ax.legend(loc=0)
fig.savefig('/home/lindsayad/gdrive/Pictures/Densities.eps',format='eps')
plt.show()
# ax.ylim((0,5e17))
