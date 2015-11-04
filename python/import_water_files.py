import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
rc('text', usetex=True)
#
mpl.rcParams.update({'font.size': 16})

f = '/home/lindsayad/gdrive/MooseOutput/H_H3Op_OH_Om.csv'

data = np.loadtxt(f,delimiter=',')
H = data[:,0]
H3Op = data[:,1]
OH = data[:,2]
Om = data[:,3]
arc_length = data[:,5]
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(arc_length,H,label='H (mol/L)',linewidth=2)
ax.plot(arc_length,H3Op,label='H$_3$O$^+$ (mol/L)',linewidth=2)
ax.plot(arc_length,OH,label='OH (mol/L)',linewidth=2)
ax.plot(arc_length,Om,label='O$^-$ (mol/L)',linewidth=2)
ax.set_xlabel('x (m)')
ax.set_ylabel('densities (mol/L)')
ax.legend(loc=0)
fig.savefig('/home/lindsayad/gdrive/Pictures/H_H3Op_OH_Om.eps',format='eps')
plt.show()
