D0 = 2.8e-9
T0 = 310.
def D(T) : return D0*T/T0*exp(3.8*373.*(1/T0-1/T))

