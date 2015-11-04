#!/usr/bin/python

import numpy as np
data = np.loadtxt('data.txt')
i = 0
total = 0.0
while i < data.size:
    total += data[i]
    i += 1
average = total/i
print average
