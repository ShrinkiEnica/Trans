from itertools import permutations
import serial
import time
from 最佳角度 import calc_min
from 最佳角度 import generate_item_layout_sequence
port = "/dev/ttyUSB0"
baudRate = 9600
# ser = serial.Serial(port,baudRate,timeout = 0.5)
ls = map(list,set(permutations([0,0,0,1,1,1])))
for item_layout_list in ls:
    one_item_layout_sequence = generate_item_layout_sequence(item_layout_list)
    print("摆放顺序:",end = '')
    print(item_layout_list)
    device_use_sequence, item_take_sequence = calc_min(one_item_layout_sequence)
    print('装置使用顺序:',end='')
    device_use_sequence_str = ''.join(str(num) for num in device_use_sequence)
    print(device_use_sequence_str)
    print('物品拿取顺序:',end='')
    item_take_sequence_str = ''.join(str(num) for num in item_take_sequence)
    print(item_take_sequence_str)
    print('\n')

item_layout_list=[1,0,1,0,1,0]
one_item_layout_sequence = generate_item_layout_sequence(item_layout_list)
device_use_sequence, item_take_sequence = calc_min(one_item_layout_sequence)

print('装置使用顺序:',end='')
device_use_sequence_str = ''.join(str(num) for num in device_use_sequence)
print(device_use_sequence_str)
print('物品拿取顺序:',end='')
item_take_sequence_str = ''.join(str(num) for num in item_take_sequence)
print(item_take_sequence_str)
print('\n')




#while (1):
#    ser.write('s'.encode())
#    ser.write(device_use_sequence_str.encode())
#    ser.write(item_take_sequence_str.encode())
