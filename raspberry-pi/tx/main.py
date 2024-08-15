import RPi.GPIO as gpio
from time import sleep
import numpy as np
from scipy.integrate import quad, dblquad

N_1 = 100
N_2 = 100
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

# G_H1 = 2
# G_L1 = 3
# G_H2 = 4
# G_L2 = 17 

# gpio.setmode(gpio.BCM)
# gpio.setup(G_H1, gpio.OUT)
# gpio.setup(G_L1, gpio.OUT)
# gpio.setup(G_H2, gpio.OUT)
# gpio.setup(G_L2, gpio.OUT)

# frequency = 10000  # 100kHz

# try:
#     while True:
#         gpio.output(G_H1, gpio.HIGH)
#         gpio.output(G_L2, gpio.HIGH)
#         gpio.output(G_H2, gpio.LOW)
#         gpio.output(G_L1, gpio.LOW)
#         sleep(0.5 / frequency)
#         gpio.output(G_H1, gpio.LOW)
#         gpio.output(G_L2, gpio.LOW)
#         gpio.output(G_H2, gpio.HIGH)
#         gpio.output(G_L1, gpio.HIGH)
#         sleep(0.5 / frequency)

# except KeyboardInterrupt:
#     gpio.cleanup()

