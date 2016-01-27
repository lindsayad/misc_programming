from sympy import *

r_e, a, mu_el, E, n, epsilon, n_gamma, epsilon_gamma, v_th, Gamma_p, mu_e, gamma_p, n_alpha, epsilon_alpha, Gamma_e, mu_i, b, n_i, v_ith, bob, e, A, R, V_bat, u = symbols('r_e a mu_el E n epsilon n_gamma epsilon_gamma v_th Gamma_p mu_e gamma_p n_alpha epsilon_alpha Gamma_e mu_i b n_i v_ith bob e A R V_bat u')

Gamma_e = (1 - r_e) / (1 + r_e) * (-(2 * a -1) * mu_e * E * n_alpha + v_th * 1 / 2 * n_alpha) - (1 - a) * gamma_p * Gamma_p
Gamma_e = Gamma_e.subs(n_alpha, n - n_gamma)
Gamma_e = Gamma_e.subs(Gamma_p, (1 - r_e) / (1 + r_e) * ((2 * b - 1) * mu_i * E * n_i + v_ith * 1 / 2 * n_i))
Gamma_p = (1 - r_e) / (1 + r_e) * ((2 * b - 1) * mu_i * E * n_i + v_ith * 1 / 2 * n_i)
J_tot = simplify(e * Gamma_p - e * Gamma_e)
soln = solve(V_bat + u - J_tot * A * R, E, dict=True)
Gamma_eps = simplify(soln[0][E])
factored = Gamma_eps.factor()
