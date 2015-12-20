#!/usr/bin/env sage
from sage.all import *

x,y = var('x,y')
u = exp(-x)*sin(pi*x)*sin(2*pi*y)
diff(u,x,2)
diff(u,y,2)
diff(u,x,2)+diff(u,y,2)
laplacian_u = _
laplacian_u
integrand = y*diff(u,y,1)
integrand
integrated = integral(integrand,y,0,1)
integrated
plot(cos(2*pi*y)*y,(y,0,1))
f = -laplacian_u + integrated
f
f.factor()
