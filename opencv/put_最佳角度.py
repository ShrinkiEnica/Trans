put_to_left_angles = [ 334, 298, 222, 172, 92, 60 ]
put_to_right_angles = [ 64, 30, 308, 270, 188, 150 ]

from itertools import permutations

put_ls = list()
for p in permutations([0,1,2,3,4,5]):
    if p.index(4) < p.index(3) and p.index(3) < p.index(2):
        put_ls.append(list(p))

for sequence in put_ls:
    angle = 0;
    current_angle = 0
    for i in sequence:
        if i == 0:
            current_angle =  put_to_left_angles[0]
        if i <=2:
            angle+= put_to_left_angles[i] - current_angle
            current_angle = put_to_left_angles[i]
        if i> 2:
            angle += put_to_right_angles[i]
            current_angle = put_to_right_angles[i]
    sequence.append(angle)
put_ls.sort(key = lambda x:x[6])
for i in put_ls:
    print(i)
