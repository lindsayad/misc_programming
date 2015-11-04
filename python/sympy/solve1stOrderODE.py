#!/usr/bin/env python

from sympy import Function, dsolve, Eq, Derivative, sin, cos, exp, symbols
from sympy.abc import x
f = Function('f')
from sympy.abc import r
from sympy.abc import s
print dsolve(Derivative((r**2)*f(r),r) + (r**2)*s*f(r), f(r))
