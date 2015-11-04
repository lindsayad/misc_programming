from sympy import *

class my_func(Function):
    @classmethod
    def eval(cls,x):
        if x.is_number:
            return x*(1-x)
