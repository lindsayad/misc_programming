from sympy import *

x,y,z,p,n = symbols('x y z p n')
expr1 = x + y * (z * p + z * n)
print is_collect_ready(expr1)

expr2 = z * p + z * n
print is_collect_ready(expr2)

expr3 = expr2 * y
print is_collect_ready(expr3)
# expr2 = collect(expr1, z)
