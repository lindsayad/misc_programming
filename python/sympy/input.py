x,y,z,n,p = symbols('x y z n p')
expr1 = z * (y * x + y * p) + n
expr2 = collect(expr1,y)
