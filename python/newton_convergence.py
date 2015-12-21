import numpy as np
import matplotlib.pyplot as plt

x = np.array([1.35e8, 2.74e7, 1.22e6, 5.59e3, 7.24e1, 1.35e1, 2.12e0, 7.38e-1])
y = np.zeros(len(x)-1)
for i in range(len(y)):
    y[i] = x[i+1]
maxim = np.max(x)
x = x/maxim
y = y/maxim
x = np.delete(x,len(x)-1)
print x
print y
linfit = np.polyfit(x,y,1)
plin = np.poly1d(linfit)
quadfit = np.polyfit(x,y,2)
pquad = np.poly1d(quadfit)
linfitplt = np.zeros(x.size)
quadfitplt = np.zeros(x.size)
for i in range(x.size):
    linfitplt[i] = plin(x[i])
    quadfitplt[i] = pquad(x[i])
print linfitplt
print quadfitplt
plt.plot(x,y,'r-',x,linfitplt,'b--',x,quadfitplt,'ko')
plt.yscale('log')
plt.xscale('log')
plt.show()

