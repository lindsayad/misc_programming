from scipy.optimize import minimize
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

# def func(x, sign=1.0):
#     """ Objective function """
#     return sign*(2*x[0]*x[1] + 2*x[0] - x[0]**2 - 2*x[1]**2)
# def func_deriv(x, sign=1.0):
#     """ Derivative of objective function """
#     dfdx0 = sign*(-2*x[0] + 2*x[1] + 2)
#     dfdx1 = sign*(2*x[0] - 4*x[1])
#     return np.array([ dfdx0, dfdx1 ])
# cons = ({'type': 'eq',
#          'fun' : lambda x: np.array([x[0]**3 - x[1]]),
#          'jac' : lambda x: np.array([3.0*(x[0]**2.0), -1.0])},
#         {'type': 'ineq',
#          'fun' : lambda x: np.array([x[1] - 1]),
#          'jac' : lambda x: np.array([0.0, 1.0])})
# res = minimize(func, [-1.0,1.0], args=(-1.0,), jac=func_deriv,
#                method='SLSQP', options={'disp': True})
# res2 = minimize(func, [-1.0,1.0], args=(-1.0,), jac=func_deriv,
#                constraints=cons, method='SLSQP', options={'disp': True})

f = '/home/lindsayad/projects/zapdos/src/materials/td_argon_mean_en.txt'
data = np.loadtxt(f)
mean_en = data[:,0]
alpha = data[:,1]
tck = interpolate.splrep(mean_en,alpha,s=0)
xnew = np.arange(np.min(mean_en),np.max(mean_en)*101./100,(np.max(mean_en)-np.min(mean_en))/100.)
ynew = interpolate.splev(xnew,tck,der=0)
plt.plot(mean_en,alpha,'o',label='true data')
plt.plot(xnew, ynew, label='interpolation')
plt.legend(loc=0)
plt.show()
# n = mean_en.size
# x = mean_en
# y = alpha
# delta_x = np.zeros(n-1)
# delta_y = np.zeros(n-1)
# a = np.ones(n-1)
# b = np.ones(n-1)
# c = np.ones(n-1)
# K = 1.0

# for i in range(n-1):
#     delta_x[i] = mean_en[i+1]-mean_en[i]
#     delta_y[i] = alpha[i+1]-alpha[i]
# m = delta_y/delta_x

# p = np.zeros(3*(n-1)+1)
# for i in range(n-1):
#     p[3*i]=a[i]
#     p[3*i+1]=b[i]
#     p[3*i+2]=c[i]
# p[3*(n-1)] = K

# def optimize_func(p,delta_x):
#     num_intervals = (p.size-1)/3
#     resid = 0
#     for i in range(num_intervals-1):
#         resid += 6.0*p[3*i]*delta_x[i] + 2.0*p[3*i+1] - 2.0*p[3*(i+1)+1] + p[p.size-1]
#     return resid

# # unconstrained_result = minimize(optimize_func,x0=np.zeros(3*(n-1)+1),args=(delta_x,),method='SLSQP',options={'disp':True})

# from itertools import chain

# # Equality constraints are set to zero
# cons10 = ({'type': 'eq',
#            'fun' : lambda p: p[0]*delta_x[0]**3+p[1]*delta_x[0]**2+p[2]*delta_x[0]+y[0]-y[1]} for i in range(1))
# cons11 = ({'type': 'eq',
#            'fun' : lambda p: p[3]*delta_x[1]**3+p[4]*delta_x[1]**2+p[5]*delta_x[1]+y[1]-y[2]} for i in range(1))
# cons12 = ({'type': 'eq',
#            'fun' : lambda p: p[6]*delta_x[2]**3+p[7]*delta_x[2]**2+p[8]*delta_x[2]+y[2]-y[3]} for i in range(1))
# # cons1 = ({'type': 'eq',
# #           'fun' : lambda p: p[3*i]*delta_x[i]**3+p[3*i+1]*delta_x[i]**2+p[3*i+2]*delta_x[i]+y[i]-y[i+1]} for i in range(n-1))
# cons2 = ({'type': 'eq',
#           'fun' : lambda p: 3.0*p[0]*delta_x[0]**2 + 2.0*p[0+1]*delta_x[0]+p[3*0+2]-p[3*(0+1)+2]} for i in range(1))
# # cons2 = ({'type': 'eq',
# #           'fun' : lambda p: 3.0*p[3*i]*delta_x[i]**2 + 2.0*p[3*i+1]*delta_x[i]+p[3*i+2]-p[3*(i+1)+2]} for i in range(n-2))

# # Inequality constraints are always meant to be positive
# cons3 = ({'type': 'ineq',
#           'fun' : lambda p: 6.0*p[3*i]*delta_x[i]+2.0*p[3*i+1]-2.0*p[3*(i+1)+1]+p[p.size-1]} for i in range(n-2))
# cons9a = ({'type': 'ineq',
#           'fun' : lambda p: p[3*i+2]} for i in range(n-1))
# cons9b = ({'type': 'ineq',
#           'fun' : lambda p: 3.0*p[3*i]*delta_x[i]**2+2.0*p[3*i+1]*delta_x[i]+p[3*i+2]} for i in range(n-1))
# cons9c = ({'type': 'ineq',
#           'fun' : lambda p: 3.0*p[3*i]*delta_x[i]**2+2.0*p[3*i+1]*delta_x[i]+3.0*m[i]} for i in range(n-1))
# cons9d = ({'type': 'ineq',
#           'fun' : lambda p: -3.0*p[3*i]*delta_x[i]**2-2.0*p[3*i+1]*delta_x[i]-3.0*p[3*i+2]+9.0*m[i]} for i in range(n-1))
# cons9e = ({'type': 'ineq',
#           'fun' : lambda p: -6.0*p[3*i]*delta_x[i]**2-4.0*p[3*i+1]*delta_x[i]-3.0*p[3*i+2]+9.0*m[i]} for i in range(n-1))
# cons9f = ({'type': 'ineq',
#           'fun' : lambda p: -3.0*p[3*i]*delta_x[i]**2-2.0*p[3*i+1]*delta_x[i]+3.0*m[i]} for i in range(n-1))
# cons9 = chain(cons9a,cons9b,cons9c,cons9d,cons9e,cons9f)

# cons = tuple(chain(cons10,cons11,cons12,cons3,cons9))
# # cons = tuple(chain(cons1,cons2,cons3,cons9))

# # constrained_result = minimize(optimize_func,x0=np.zeros(3*(n-1)+1),args=(delta_x,),method='SLSQP',options={'disp':True})
# constrained_result = minimize(optimize_func,x0=np.zeros(3*(n-1)+1),args=(delta_x,),method='SLSQP',options={'disp':True, 'maxiter':1000},constraints=cons)

# # Currently, I get a singular matrix when I include any of my equality constraints. I can get the optimization to terminate successfully if I use just the inequality constraints."
