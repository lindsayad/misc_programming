# coding: utf-8
from sympy import *
f = symbols('f', cls=Function)
f(x)
x, t, uj = symbols('x t uj')
f(x)
diff(f(x),x)
phi = symbols('phi', cls=Function)
diff(uj*phi(x),uj)
diff(uj*phi(x),x)
g = symbols('g')
g = uj*phi(x)
g
diff(g,x)
diff(g,uj)
u = symbols('u')
u = g
u
grad_u = symbols('grad_u')
grad_u = diff(u,x)
grad_u
diff(grad_u,uj)
get_ipython().magic(u'history')
beta_h, beta = symbols('beta_h beta')
beta_h = beta*grad_u/(grad_u*grad_u)*grad_u
diff(beta_h,uj)
beta_h
get_ipython().magic(u'history')
v1 = Matrix([1,2,3])
v2 = Matrix([4,5,6])
v1.dot(v2)
u
u = uj*phi(x,y,z)
y, z = symbols('y z')
u = uj*phi(x,y,z)
u
a1 = diff(u,x)
a2 = diff(u,y)
a3 = diff(u,z)
grad_u = Matrix([a1,a2,a3])
grad_u
beta = Matrix([b1,b2,b3])
b1, b2, b3, bh1, bh2, bh3 = symbols('b1 b2 b3 bh1 bh2 bh3')
beta = Matrix([b1,b2,b3])
betah = Matrix([bh1,bh2,bh3])
betah = beta.dot(grad_u)/grad_u.dot(grad_u)*grad_u
betah
simplify(_)
diff(betah,uj)
betah[0]
diff(betah[0],uj)
simplify(_)
phi1, phi2, phi3, phi4 = symbols('phi1 phi2 phi3 phi4',cls=Function)
u1 = uj*phi1(x)
u2 = uj*phi2(x)
u3 = uj*phi3(x)
u4 = uj*phi4(x)
for i in range(1,4):
    grad_u + str(i) = diff(u+str(i),x)
    
u1
i = 1
u+str(i)
u
print u+str(i)
str(u)
str(u+i)
str(u)+str(i)
symbol(str(u)+str(i))
test = symbol(str(u)+str(i))
test = symbol('str(u)+str(i)')
u1
grad_u1 = diff(u1,x)
grad_u2 = diff(u2,x)
grad_u3 = diff(u3,x)
grad_u4 = diff(u4,x)
beta
beta = symbol('beta')
test = symbols('str(u)+str(i)')
test
test = symbols(str(u)+str(i))
test
diff(test,x)
beta = symbols('beta')
betah = beta*grad_u1/(grad_u2*grad_u3)*grad_u4
diff(betah,uj)
betah
u = uj*phi(x,y)
a1 = diff(u,x)
a2 = diff(u,y)
grad_u = Matrix([a1,a2])
grad_u
beta = Matrix([b1,b2])
beta.dot(grad_u)
grad_u.dot(grad_u)
num = beta.dot(grad_u)
denom = grad_u.dot(grad_u)
betah = num / denom * grad_u
simplify(betah)
diff(simplify(betah),uj)
phi1
phi1(x)
phi2(x)
u1
u1, u2 = symbols('u1 u2')
u = u1*phi1(x,y) + u2*phi2(x,y)
a1 = diff(u,x)
a2 = diff(u,y)
grad_u = Matrix([a1,a2])
beta
betah = beta.dot(grad_u)/grad_u.dot(grad_u)*grad_u
simplify(betah)
simplify(betah[0])
diff(_,u1)
simplify(_)
u
expr = u1*phi1(x, y) + u2*phi2(x, y)
expr.rewrite(u)
u
type(u)
type(x)
type(phi)
u.rewrite(phi1,phi2)
srepr(u)
u
z = exp(x)
diff(z,x)
type(z)
expr = exp(x)
expr
expr.rewrite(z)
z
expr = diff(z,x)
expr
expr.subs(exp(x),z)
new_expr = expr.subs(exp(x),z)
new_expr
expr
new_expr = expr.subs(exp(x),blah)
blah = symbols('blah')
new_expr = expr.subs(exp(x),blah)
new_expr
betah
new_betah = betah.subs(u,blah)
new_betah
grad_u
simplify(new_betah)
simplify(betah[0])
ux = Diff(u,x)
ux = diff(u,x)
type(ux)
ux
vx = symbols('vx')
betah[0].subs(ux,vx)
uy = diff(u,y)
vy = symbols('vy')
bh1 = betah[0].subs([(ux,vx),(uy,vy)])
bh1
betah[0]
bh1u1 = diff(betah[0],u1)
bh1u1
grad_u_squared = vx**2 + vy**2
bh1u1_simp = bh1u1.subs([(ux,vx),(uy,vy)])
bh1u1_simp
grad_v_squared = symbols('grad_v_squared')
bh1u1_simp = bh1u1_simp.subs(grad_u_squared,grad_v_squared)
bh1u1_simp
grad_v = Matrix([vx,vy])
beta.dot(grad_v)
beta_dot_grad_u = beta.dot(grad_v)
beta_dot_grad_v = symbols('beta_dot_grad_v')
bh1u1_simp = bh1u1_simp.subs(beta_dot_grad_u,beta_dot_grad_v)
bh1u1_simp
simplify(bh1u1_simp)
grad_phi1 = Matrix([diff(phi1(x,y),x),diff(phi1(x,y),y)])
beta_dot_grad_phi1 = beta.dot(grad_phi1)
beta_dot_grad_psi1 = symbols('beta_dot_grad_psi1')
bh1u1_simp = bh1u1_simp.subs(beta_dot_grad_phi1,beta_dot_grad_psi1)
bh1u1_simp
simplify(_)
grad_u
grad_v
grad_v_dot_grad_psi1 = symbols('grad_v_dot_grad_psi1')
bh1u1_simp = bh1u1_simp.subs(grad_v.dot(grad_phi1),grad_v_dot_grad_psi1)
bh1u1_simp
simplify(_)
bh1u1_simp = _
bh1u1_simp
bh1u1_simp = bh1u1_simp.subs(grad_v.dot(grad_phi1),grad_v_dot_grad_psi1)
bh1u1_simp
bh1u1_final = _
betah[1]
bh2u1 = diff(betah[1],u1)
bh2u1
type(v)
get_ipython().magic(u'history')
get_ipython().magic(u'save computeJacobianSession 1-194')
