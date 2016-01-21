r_e, a, mu_el, E, n, epsilon, n_gamma, epsilon_gamma, v_th, Gamma_p, mu_e, gamma_p, n_alpha, epsilon_alpha, Gamma_e, mu_i, b, n_i, v_ith, bob, e, A, R, V_bat, u = symbols('r_e a mu_el E n epsilon n_gamma epsilon_gamma v_th Gamma_p mu_e gamma_p n_alpha epsilon_alpha Gamma_e mu_i b n_i v_ith bob e A R V_bat u')
# n_gamma = (1 - a) * gamma_p * Gamma_p / (mu_e * E)
# eq1 = (1 - r_e) / (1 + r_e) * (-(2 * a -1) * mu_el * E * n_alpha * epsilon_alpha + v_th * 5 / 6 * n_alpha * epsilon_alpha) - (1 - a) * 5 / 3 * epsilon_gamma * gamma_p * Gamma_p
# eq2 = eq1.subs(n_alpha * epsilon_alpha, n * epsilon - n_gamma * epsilon_gamma)
# eq3 = simplify(eq2)
Gamma_e = (1 - r_e) / (1 + r_e) * (-(2 * a -1) * mu_e * E * n_alpha + v_th * 1 / 2 * n_alpha) - (1 - a) * gamma_p * Gamma_p
Gamma_e = Gamma_e.subs(n_alpha, n - n_gamma)
Gamma_e = simplify(Gamma_e)
# eq3 = eq2.subs(n_gamma, (1 - a) * gamma_p * Gamma_p / (mu_e * E))

# Gamma_e = Gamma_e.subs(Gamma_p, (1 - r_e) / (1 + r_e) * ((2 * b - 1) * mu_i * E * n_i + v_ith * 1 / 2 * n_i))
# Gamma_e = Gamma_e.subs(Gamma_p, bob)
Gamma_e = simplify(Gamma_e.subs(Gamma_p, (1 - r_e) / (1 + r_e) * ((2 * b - 1) * mu_i * E * n_i + v_ith * 1 / 2 * n_i)))
Gamma_p = (1 - r_e) / (1 + r_e) * ((2 * b - 1) * mu_i * E * n_i + v_ith * 1 / 2 * n_i)
J_tot = simplify(e * Gamma_p - e * Gamma_e)
soln = solve(V_bat + u - J_tot * A * R, E, dict=True)
