%paste
x = var('x')
y = function('y',x)
de = -diff(y,x,2) + diff(y,x)
f = desolve(de,y,ics[0,1,1,0])
f = desolve(de,y,ics=[0,1,1,0])
f
plot(f)
help(plot)
plot(f,xmin=0,xmax=1)
cd ~/zapdos/problems
import numpy as np
data = np.loadtxt("dg_advection_diffusion.csv",delimiter=',')
data[:,0]
y_moose = data[:,0]
x_moose = data[:,1]
plot(x_moose,y_moose)
f
help(list_plot)
list_plot(data)
data = np.loadtxt("dg_advection_diffusion.csv",delimiter=',')
list_plot(data)
moose = list_plot(data)
analytic = plot(f)
analytic = plot(f,xmin=0,xmax=1)
show(moose+analytic)
%history > moose_vs_analytic.sage
pwd
cd -
cd -
%history -f moose_vs_analytic.sage
solve(de,f)
solve(de,y)
de
desolve(de,y)
g = _
g
g(0)
g = desolve(de,y)
g(0)
gp = diff(y,x)
gp
gp = diff(g,x)
gp
gp(0)
gp(1)
g(x=0)
solve([g(x=0)==1, gp(x=1) + g(x=1) == 0], _K1, _K2)
var('_K1','_K2')
solve([g(x=0)==1, gp(x=1) + g(x=1) == 0], _K1, _K2)
_K1, _K2 = solve([g(x=0)==1, gp(x=1) + g(x=1) == 0], _K1, _K2)
[[_K1, _K2]] = solve([g(x=0)==1, gp(x=1) + g(x=1) == 0], _K1, _K2)
_K1
_K2
g
g(_K1=_K1,_K2=_K2)
sol = solve([g(x=0)==1, gp(x=1) + g(x=1) == 0], _K1, _K2, solution_dict=True)
_K1
_K2
clear(_K1)
%history -f moose_vs_analytic.sage
pwd
cd -
cd ~/gdrive/programming/sage
cd ~/gdrive/programming/python/sage
g = desolve(de,y)
g
_K1
reset(_K1)
reset('_K1')
_K1
reset('_K2')
%paste
var('_K1','_K2')
sol = solve([g(x=0)==1, gp(x=1) + g(x=1) == 0], _K1, _K2, solution_dict=True)
g
g.subs(sol[0])
g
g = g.subs(sol[0])
g
plot(g,xmin=0,xmax=1)
plot(g,xmin=0,xmax=1,ymin=0,ymax=1)
%history -f moose_vs_analytic.sage