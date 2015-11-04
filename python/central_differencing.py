import numpy as np
x = np.array([0,1,2,3,5,8,13])
dx = np.gradient(x)
dx
y=x**2
np.gradient(y,dx,edge_order=2)

dx1 = np.zeros(x.shape)
dx2 = np.zeros(x.shape)
a = np.zeros(x.shape)
b = np.zeros(x.shape)
c = np.zeros(x.shape)
yprime = np.zeros(x.shape)

for i in range(1,x.size-1):
    dx1[i] = x[i]-x[i-1]
    dx2[i] = x[i+1]-x[i]
    a[i] = -dx2[i]/(dx1[i]*(dx1[i]+dx2[i]))
    b[i] = (dx2[i]-dx1[i])/(dx1[i]*dx2[i])
    c[i] = dx1[i]/(dx2[i]*(dx1[i]+dx2[i]))
    yprime[i] = a[i]*y[i-1]+b[i]*y[i]+c[i]*y[i+1]                   

dx2[0] = x[1]-x[0]
a[0] = -(2*dx2[0]+dx2[1])/(dx2[0]*(dx2[0]+dx2[1]))
b[0] = (dx2[0]+dx2[1])/(dx2[0]*dx2[1])
c[0] = -dx2[0]/(dx2[1]*(dx2[0]+dx2[1]))
yprime[0] = a[0]*y[0]+b[0]*y[1]+c[0]*y[2]

dx1[x.size-1] = x[x.size-1]-x[x.size-2]
a[x.size-1] = dx1[x.size-1]/(dx1[x.size-2]*(dx1[x.size-2]+dx1[x.size-1]))
b[x.size-1] = -(dx1[x.size-1]+dx1[x.size-2])/(dx1[x.size-1]*dx1[x.size-2])
c[x.size-1] = (2*dx1[x.size-1]+dx1[x.size-2])/(dx1[x.size-1]*(dx1[x.size-1]+dx1[x.size-2]))
yprime[x.size-1] = a[x.size-1]*y[x.size-3] + b[x.size-1]*y[x.size-2] + c[x.size-1]*y[x.size-1]
