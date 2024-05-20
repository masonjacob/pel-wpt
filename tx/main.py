import RPi.GPIO as gpio
from time import sleep
import math

G_H1 = 2
G_L1 = 3
G_H2 = 4
G_L2 = 17 

gpio.setmode(gpio.BCM)
gpio.setup(G_H1, gpio.out)
gpio.setup(G_L1, gpio.out)
gpio.setup(G_H2, gpio.out)
gpio.setup(G_L2, gpio.out)

frequency = 100000  # 100kHz

try:
    while True:
        gpio.output(G_H1, gpio.HIGH)
        gpio.output(G_L2, gpio.HIGH)
        gpio.output(G_H2, gpio.LOW)
        gpio.output(G_L1, gpio.LOW)
        sleep(0.5 / frequency)
        gpio.output(G_H1, gpio.LOW)
        gpio.output(G_L2, gpio.LOW)
        gpio.output(G_H2, gpio.HIGH)
        gpio.output(G_L1, gpio.HIGH)
        sleep(0.5 / frequency)

except KeyboardInterrupt:
    gpio.cleanup()