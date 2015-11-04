import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import rc
rc('text', usetex=True)
#
mpl.rcParams.update({'font.size': 16})

f = '/home/lindsayad/gdrive/MooseOutput/potential_energy.csv'

data = np.loadtxt(f,delimiter=',')
pot = data[:,0]
arc_length = data[:,2]
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(arc_length,pot,label='zapdos potential',linewidth=2)
ax.set_xlabel('x (m)')
ax.set_ylabel('Potential (V)')
ax.legend(loc=0)
fig.savefig('/home/lindsayad/gdrive/Pictures/Potential.eps',format='eps')
plt.show()
