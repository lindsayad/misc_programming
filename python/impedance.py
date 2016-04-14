import math
from sympy.physics import units
from sympy import I
from sympy import sqrt
from constants import constants as c

def impedance(f, m, n_0, A, d, eps_r, mu = None, nu_m = None):

    w = 2 * math.pi * f
    # print "w is " + str(w)

    if mu is not None:
        nu_m = c.e / (mu * m)
    elif nu_m is not None:
        nu_m = nu_m
    else:
        raise Exception('You must supply either mu or nu_m')
    lossless_eps = eps_r * c.eps0

    w_c = sqrt(c.e**2 * n_0 / (lossless_eps * m))
    # print "w_c is " + str(w_c)
    eps = lossless_eps * (1. - w_c**2 / (w * (w - nu_m * I)))
    # print "eps is " + str(eps)

    Yp =  w * eps * A / d * I
    # print "Yp is equal to " + Yp
    Zp = 1. / Yp
    return eps, Yp, Zp
