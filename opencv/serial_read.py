import time
from pyb import UART

uart = UART(3,9600,timeout_char = 1000)

while True:
    if uart.any():
        a = uart.readline()
        print(a)
