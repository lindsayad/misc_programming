r_e, a, mu_el, E, n, epsilon, n_gamma, epsilon_gamma, v_th, Gamma_p, mu_e, gamma_p, n_alpha, epsilon_alpha = symbols('r_e a mu_el E n epsilon n_gamma epsilon_gamma v_th Gamma_p mu_e gamma_p n_alpha epsilon_alpha')
# n_gamma = (1 - a) * gamma_p * Gamma_p / (mu_e * E)
eq1 = (1 - r_e) / (1 + r_e) * (-(2 * a -1) * mu_el * E * n_alpha * epsilon_alpha + v_th * 5 / 6 * n_alpha * epsilon_alpha) - (1 - a) * 5 / 3 * epsilon_gamma * gamma_p * Gamma_p
eq2 = eq1.subs(n_alpha * epsilon_alpha, n * epsilon - n_gamma * epsilon_gamma)
eq3 = simplify(eq2)
# eq1 = (1 - r_e) / (1 + r_e) * (-(2 * a -1) * mu_e * E * n_alpha + v_th * 1 / 2 * n_alpha) - (1 - a) * gamma_p * Gamma_p
# eq2 = eq1.subs(n_alpha, n - n_gamma)
# eq3 = eq2.subs(n_gamma, (1 - a) * gamma_p * Gamma_p / (mu_e * E))
