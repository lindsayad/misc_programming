VThreshold=7.0
VHyster=0.5
RPlas=1.0
RAir=10.e6
Aconst=log(RAir/RPlas)/pi
Bconst=log(1/(RAir*RPlas))/2.0
vPlas=6.272221
rVar = 1.0/exp(Aconst * atan((vPlas-VThreshold)/abs(VHyster))+Bconst)
print n(rVar)


