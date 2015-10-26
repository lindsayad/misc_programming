#!/usr/bin/env sage
from sage.all import *

y = var('y')
f = lambda p: -p[0]-p[1]+50
c_1 = lambda p: p[0]-45
c_2 = lambda p: p[1]-5
c_3 = lambda p: -50*p[0]-24*p[1]+2400
c_4 = lambda p: -30*p[0]-33*p[1]+2100
a = minimize_constrained(f,[c_1,c_2,c_3,c_4],[2,3])
print a
