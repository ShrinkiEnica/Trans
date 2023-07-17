import serial
import time
from 最佳角度 import calc_min
port = "/dev/ttyUSB0"
baudRate = 9600
ser = serial.Serial(port,baudRate,timeout = 0.5)
one_item_layout_sequence = [0,0,0,1,1,1]
device_use_sequence, item_take_sequence = calc_min()
device_use_sequence_str = ''.join(str(num) for num in device_use_sequence)
item_take_sequence_str = ''.join(str(num) for num in item_take_sequence)
while (1):
    ser.write('s'.encode('ascii'))
    ser.write('1'.encode('ascii'))
