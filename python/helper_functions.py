import numpy as np

def indep_array(start, finish, num_steps):
    x = np.zeros(num_steps)
    for i in range(0, num_steps):
        x[i] = start * ((finish / start) ** (1. / (num_steps - 1.))) ** i
    return x
