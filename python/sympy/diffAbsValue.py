#!/usr/bin/env python

from sympy import *
class MyAbs(Abs):
    def _eval_derivative(self, x):
        return Derivative(self.args[0], x, evaluate=True)*sign(conjugate(self.args[0]))
x = Symbol('x')
y = x/MyAbs(x)
print simplify(diff(y,x))
