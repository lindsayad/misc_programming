t,Cap,R2,R1,Vc,Ron,Roff,VthreshOn,VthreshOff,Vthresh = var('t Cap R2 R1 Vc Ron Roff VthreshOn VthreshOff Vthresh')
assume(t,'real')
Cap, R1, Vc = 1., 1., 1.
Ron = .1
Roff = 10
VthreshOn = 0.908
VthreshOff = 0.85
R2 = Roff
Vthresh = VthreshOn
Vp = function('Vp',t)
Vpvar = desolve(Cap*diff(Vp,t) + Vp/R2 + Vp/R1 - Vc/R1, Vp, ivar=t, ics=[0,0])
print Vpvar
#assume(t,'real')
sol = solve(Vpvar==Vthresh,t,solution_dict=True)
[[tc]]=[[s[t]] for s in sol]
print n(tc)
a = plot([])
b = plot([])
tcOld = 0.0
IPlasma = Vpvar/R2
a += plot(Vpvar,(tcOld,tc))
b += plot(IPlasma,(tcOld,tc))
numSteps = 7
i = 1
while i <= numSteps:
	if i % 2 == 0: 
		R2 = Roff
		Vthresh = VthreshOn
	else:
		R2 = Ron
		Vthresh = VthreshOff
	Vpvar = desolve(Cap*diff(Vp,t) + Vp/R2 + Vp/R1 - Vc/R1, Vp, ivar=t, ics=[tc,Vpvar(t=tc)])
	print Vpvar
#	assume(t,'real')
	sol = solve(Vpvar==Vthresh,t,solution_dict=True)
#	print sol
	tcOld = tc
	[[tc]]=[[s[t]] for s in sol]
	print 'Here comes tc'
#	print tc
	print n(tc)
#	print 'Here comes Vplasma'
#	print Vpvar(t=tc)
#	print n(Vpvar(t=tc))
	IPlasma = Vpvar/R2
	a += plot(Vpvar,(tcOld,tc))
	b += plot(IPlasma,(tcOld,tc))
	i += 1
a.show()
b.show()
c = plot(IPlasma,(tcOld,tc))
#c.show()
#
#
#
#
##################################################################################
#
#R2 = Roff
#Vpvar0 = desolve(Cap*diff(Vp,t) + Vp/R2 + Vp/R1 - Vc/R1, Vp, ivar=t, ics=[0,0])
#tc0 = find_root(Vpvar0==0.5,0,10.0)
#print tc0
#R2 = Ron
#Vpvar1 = desolve(Cap*diff(Vp,t) + Vp/R2 + Vp/R1 - Vc/R1, Vp, ivar=t, ics=[tc0,Vpvar0(t=tc0)])
#tc1 = find_root(Vpvar1==0.25,tc0,tc0+3*tc0)
#print tc1
#R2 = Roff
#Vpvar2 = desolve(Cap*diff(Vp,t) + Vp/R2 + Vp/R1 - Vc/R1, Vp, ivar=t, ics=[tc1,Vpvar1(t=tc1)])
#tc2 = find_root(Vpvar2==0.5,tc1,tc1+3*tc1)
#print tc2
#a = plot([])
#a += plot(Vpvar0,(0,tc0))
#a += plot(Vpvar1,(tc0,tc1))
#a += plot(Vpvar2,(tc1,tc2))
#a.show()
#VpIC = f(tc)
#a = var('a')
#f(a)
