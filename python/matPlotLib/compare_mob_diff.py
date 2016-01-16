import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

rc('text', usetex=True)

f = "/home/lindsayad/zapdos/src/materials/td_argon_mean_en_mu_diff.txt"

mean_en, mob, diff = np.loadtxt(f, unpack = True)
diff_calc = mob * 2. / 3. * mean_en

fig = plt.figure()
ax = plt.subplot(111)
ax.plot(mean_en, diff, label = "Boltzmann")
ax.plot(mean_en, diff_calc, label = "Einstein")
ax.set_xlabel('Mean energy (V)')
ax.set_ylabel('Diffusivity (m$^2$s$^{-1}$)')
ax.legend(loc=0)
fig.savefig('/home/lindsayad/Pictures/boltzmann_vs_einstein_for_diffusivity.eps', format='eps')
plt.show()
