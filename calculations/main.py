photodiode_current = 4e-6
voltage_drop = 0.5
resistor_value = voltage_drop / photodiode_current
print(resistor_value)


on_voltage = 1.8
# gain = 1 + (Ra / Rb)
gain = 5 / 1.8
Ra = 10e3
Rb = Ra / (gain - 1)
print(Rb)
# Rb = 5.7k
