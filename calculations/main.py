# photodiode_current = 4e-6
# voltage_drop = 0.5
# resistor_value = voltage_drop / photodiode_current
# print(resistor_value)


# on_voltage = 1.8
# # gain = 1 + (Ra / Rb)
# gain = 5 / 1.8
# Ra = 10e3
# Rb = Ra / (gain - 1)
# print(Rb)
# # Rb = 5.7k

import numpy as np
from scipy.integrate import quad, dblquad

R_s = 0.140 # measured
N_1 = 20
N_2 = 20
μ_0 = 0.1
r_1 = 0.1
r_2 = 0.1
c = 0.1
d = 0.1
alpha = 0
theta = 0.5
omega = 0.5
func = (r_1 * r_2  * ((np.sin(theta) * np.sin(omega)) + (np.cos(alpha) * np.cos(theta) * np.cos(omega))) / np.sqrt((r_1 * np.cos(theta) - r_2 * np.cos(omega))^2 + (r_1 * np.sin(theta) - r_2 * np.sin(omega) * np.cos(alpha) - c)^2 +(r_2 * np.sin(omega) * np.sin(alpha) - d)^2))
coefficent = (N_1 * N_2 * μ_0) / (4 * np.pi)
print(dblquad(lambda theta, omega: func , 0, 2 * np.pi, lambda theta: 0, lambda theta: 2 * np.pi))