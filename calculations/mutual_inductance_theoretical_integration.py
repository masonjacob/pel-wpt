import numpy as np
from scipy.integrate import quad, dblquad

Ri1 = .0315
Ri2 = .0315
s1 = .0035
s2 = .0035
N1 = 20
N2 = 20

x2 = 0
y2 = 0
z2 = .02

gamma = 0
beta = 20 * (np.pi/180)
alpha = 0

R_s = 0.140 # measured
μ0 = 0.1

func = lambda theta2, theta1: ((Ri1 + (s1) / (2 * np.pi) * theta1) * np.cos(theta1) * ((Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(theta2) * (np.cos(alpha) * np.cos(gamma) + np.sin(alpha) * np.sin(beta) * np.sin(gamma)) - (Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(beta) * np.sin(alpha) * np.sin(theta2)) \
                            - (Ri1 + (s1) / (2 * np.pi) * theta1) * np.sin(theta1) * ((Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(theta2) * (-np.cos(gamma) * np.sin(alpha) + np.cos(alpha) * np.sin(beta) * np.sin(gamma)) - (Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(alpha) * np.cos(beta) * np.sin(theta2))) / \
                            (np.sqrt((z2 - (Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(theta2) * np.sin(beta) + (Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(beta) * np.sin(gamma) * np.sin(theta2)) ** 2 \
                            + (x2 - (Ri1 + (s1) / (2 * np.pi) * theta1) * np.cos(theta1) + (Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(alpha) * np.cos(beta) * np.cos(theta2) + (Ri2 + (s2) / (2 * np.pi) * theta2) * (- np.cos(gamma) * np.sin(alpha) + np.cos(alpha) * np.sin(beta) * np.sin(gamma)) * np.sin(theta2)) ** 2 \
                            + (y2 + (Ri2 + (s2) / (2 * np.pi) * theta2) * np.cos(beta) * np.cos(theta2) * np.sin(alpha) - (Ri1 + (s1) / (2 * np.pi) * theta1) * np.sin(theta1) + (Ri2 + (s2) / (2 * np.pi) * theta2) * (np.cos(alpha) * np.cos(gamma) + np.sin(alpha) * np.sin(beta) * np.sin(gamma)) * np.sin(theta2)) ** 2))

integral = dblquad(func , 0, 2 * np.pi * N2, lambda theta1: 0, lambda theta1: 2 * np.pi * N1)
coefficent = (μ0) / (4 * np.pi)
result = coefficent * integral
print(result)



# R_alpha = np.matrix([[np.cos(alpha), -np.sin(alpha), 0], [np.sin(alpha), np.cos(alpha), 0], [0, 0, 1]])
# R_beta = np.matrix([[np.cos(beta), 0, np.sin(beta)], [0, 1, 0], [-np.sin(beta), 0, np.cos(beta)]])
# R_gamma = np.matrix([[1, 0, 0], [0, np.cos(gamma), -np.sin(gamma)], [0, np.sin(gamma), np.cos(gamma)]])

# R = R_alpha @ R_beta @ R_gamma

# R_all = np.matrix([[np.cos(alpha)*np.cos(beta), -np.sin(alpha)*np.cos(gamma) + np.cos(alpha)*np.sin(beta)*np.sin(gamma), np.sin(alpha)*np.sin(gamma) + np.cos(alpha)*np.sin(beta)*np.cos(gamma)], 
#                    [np.sin(alpha)*np.cos(beta), np.cos(alpha)*np.cos(gamma) + np.sin(alpha)*np.sin(beta)*np.sin(gamma), -np.cos(alpha)*np.sin(gamma) + np.sin(alpha)*np.sin(beta)*np.cos(gamma)], 
#                    [-np.sin(beta), np.cos(beta)*np.sin(gamma), np.cos(beta)*np.cos(gamma)]])

# print(R)
# print(R_all)

# P_A = np.matrix([0, c, d])

# T = np.eye(4)
# T[0:3, 0:3] = R
# T[0:3, 3] = P_A

# Q_B = np.matrix([[10], [0], [5], [1]])
# Q_A = T @ Q_B

# r1 = Ri1 + (s1)/(2*np.pi)*theta1
# r2 = Ri2 + (s2)/(2*np.pi)*theta2
# print(r1, r2)
# dist = np.sqrt((r1*np.cos(theta1) - r2*np.cos(theta2))**2 + (r1*np.sin(theta1) - r2*np.sin(theta2)*np.cos(alpha) - c)**2 + (r2*np.sin(theta2)*np.sin(alpha) - d)**2)
# print(dist)