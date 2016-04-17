import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import matplotlib as mpl
rc('text', usetex=True)
mpl.rcParams.update({'font.size': 18})

x = np.linspace(0,10)
y = -x**2
plt.plot(x, -y, label = r"$|$Im(Z)$|$")
plt.legend()
plt.show()
