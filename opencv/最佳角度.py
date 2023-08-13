import itertools
import numpy as np


class TakeDevice:
    def __init__(self, claw_0_suck_1: int, device_index: int, take_angles):
        """
        :param sucker_or_claw: 对应的是否拿取物品
        :param device_index: 在3个悬臂上的顺序
        """
        self.is_take = False
        self.claw_0_suck_1 = claw_0_suck_1
        self.arm_index = device_index
        self.take_angles = take_angles


class ColaBox:
    def __init__(self, cola_0_box_1: int, index: int):
        """
        """
        self.cola_0_box_1 = cola_0_box_1
        self.taken_device_index = -1
        self.index = index


def generate_item_layout_sequence(cola_0_box_1_list: list[int]) -> list[ColaBox]:
    ret_list = list()
    for i in range(6):
        ret_list.append(ColaBox(cola_0_box_1_list[i], i))
    return ret_list


def generate_device_layout_sequence(claw_0_sucker_1_list: list[int]) -> list[TakeDevice]:
    return [TakeDevice(claw_0_sucker_1_list[i], i, device_take_angles[i]) for i in range(6)]


def generate_device_use_sequence(item_layout_sequence: list[ColaBox],
                                 item_take_sequence: list[int],
                                 device_layout_seqeunce: list[TakeDevice]):
    all_device_use_sequence = list(itertools.permutations([0, 1, 2, 3, 4, 5]))
    valid_device_use_sequence = list()
    for device_use_sequence in all_device_use_sequence:
        if all([device_layout_seqeunce[device_use_sequence[i]].claw_0_suck_1 == item_layout_sequence[item_take_sequence[i]].cola_0_box_1 for i in range(6)]):
            valid_device_use_sequence.append(list(device_use_sequence))
    return valid_device_use_sequence


def generate_device_take_angles():
    ret_list = list()
    def gen(list, index): return list[1:] if index == 0 else list[:-1]
    for i in range(6):
        index = i % 2
        if i // 2 == 0:
            ret_list.append(gen(angles_1_1, index))
        if i // 2 == 1:
            ret_list.append(gen(angles_2_1, index))
        if i // 2 == 2:
            ret_list.append(gen(angles_3_1, index))
    return ret_list


def verify_feasibility(item_layout_sequence: list[ColaBox],
                       device_layout_sequence: list[TakeDevice],
                       item_take_sequence: list[int]) -> list[list[int]]:
    """
    验证方案是否可行
    :param item_layout_sequence: 物品摆放顺序
    :param device_layout_sequence: 悬臂摆放顺序
    :param item_take_sequence: 物品拿取顺序
    """
    valid_device_use_sequences = generate_device_use_sequence(item_layout_sequence,
                                                              item_take_sequence,
                                                              device_layout_sequence)
    if (item_take_sequence == [5, 0, 4, 1, 2, 3] and ls == [1, 0, 1, 0, 1, 0]):
        pass
    can_use_device_use_sequences = list()
    # 对每一个可能的device_use_sequence进行尝试,如果可以那么将其加入到can_use_device_use_sequences内
    for device_use_sequence in valid_device_use_sequences:
        # 初始化
        for device in device_layout_sequence:
            device.is_take = False
        for item in item_layout_sequence:
            item.taken_device_index = -1
        cant_use = False

        for index in range(6):
            device = device_layout_sequence[device_use_sequence[index]]
            # 如果当前位于臂的1号位
            if device.arm_index % 2 == 0:
                # 如果要拿的是前方摆放东西的5号位，那么不用考虑，肯定可以
                if item_take_sequence[index] == 5:
                    pass
                    # 2号位拿了东西和2号位下的地上有东西不能同时发生
                    # 注意这里地方有东西是taken_device_index=-1代表没有被拿
                elif device_layout_sequence[device.arm_index+1].is_take == True and item_layout_sequence[device_use_sequence[index] + 1].taken_device_index == -1:
                    cant_use = True
                    break
                elif device.arm_index == 4 and item_layout_sequence[item_take_sequence[index] + 1].cola_0_box_1 == 0 and item_layout_sequence[item_take_sequence[index] + 1].taken_device_index == -1:
                    cant_use = True
                    break
                elif device.arm_index == 2 and item_layout_sequence[item_take_sequence[index] + 1].cola_0_box_1 == 1 and item_layout_sequence[item_take_sequence[index] + 1].taken_device_index == -1:
                    cant_use = True
                    break
                elif device.arm_index == 0 and item_layout_sequence[item_take_sequence[index] + 1].cola_0_box_1 == 0 and item_layout_sequence[item_take_sequence[index] + 1].taken_device_index == -1:
                    cant_use = True
                    break
            elif device.arm_index % 2 == 1:
                # 如果要拿的是前方摆放东西的0号位，那么不用考虑，肯定可以
                if item_take_sequence[index] == 0:
                    pass
                elif device_layout_sequence[device.arm_index-1].is_take == True and item_layout_sequence[item_take_sequence[index]-1].taken_device_index == -1:
                    cant_use = True
                    break
                elif device.arm_index == 5 and item_layout_sequence[item_take_sequence[index] - 1].cola_0_box_1 == 1 and item_layout_sequence[item_take_sequence[index] - 1].taken_device_index == -1:
                    cant_use = True
                    break
                elif device.arm_index == 3 and item_layout_sequence[item_take_sequence[index] - 1].cola_0_box_1 == 1 and item_layout_sequence[item_take_sequence[index] - 1].taken_device_index == -1:
                    cant_use = True
                    break
                elif device.arm_index == 1 and item_layout_sequence[item_take_sequence[index] - 1].cola_0_box_1 == 0 and item_layout_sequence[item_take_sequence[index] - 1].taken_device_index == -1:
                    cant_use = True
                    break
            # 进行拿取操作
            item_layout_sequence[item_take_sequence[index]
                                 ].taken_device_index = device.arm_index
            device.is_take = True
        # 如果当前的不能用，那么就进行下一个device_use_sequence的试错
        if cant_use == True:
            continue
        else:
            # print(device_use_sequence)
            can_use_device_use_sequences.append(device_use_sequence)
    # print(len(valid_device_use_sequences))
    # print(can_use_num)
    return can_use_device_use_sequences


angles_1_1 = [74, 110, 142, 178, 214, 250, 286]
angles_2_1 = [314, 352, 24, 64, 102, 136, 170]
angles_2_1 = [312, 350, 26, 58, 94, 132, 168]
angles_3_1 = [196, 228, 264, 300, 334, 14, 48]
center_angles = [122, 160, 160, 160, 160, 160, 160]

min_angle_sum = 0

device_take_angles = generate_device_take_angles()


all_item_layout_sequence = [generate_item_layout_sequence(ls) for ls in map(
    list, set(itertools.permutations([0, 0, 0, 1, 1, 1])))]
one_device_layout_sequence = generate_device_layout_sequence([
    1, 1, 0, 0, 0, 1])
# one_item_layout_sequence  = generate_item_layout_sequence([0,1,0,0,1,1])
# one_item_take_sequence = [0,1,2,3,4,5]


def calc_min(one_item_layout_sequence: list[ColaBox]):
    """
    参数：元素为ColaBox对象的列表
    """
    min_angles_list = list()
    # 返回哪一号take_device拿取item的角度

    def angle(item_to_be_take: ColaBox, device_to_take: TakeDevice):
        return device_to_take.take_angles[item_to_be_take.index]
    # 返回角度最小的那一个list

    def min_sublist(ls: list):
        min_val = min(x[0] for x in ls)
        min_sublist = [x for x in ls if x[0] == min_val]
        return min_sublist[0]
    # 根据循环次数调用上面的angle函数计算角度

    def calc_angle(index): return angle(
        # item_take_sequence和device_use_seqeunces是一一对应的
        one_item_layout_sequence[one_item_take_sequence[index]], one_device_layout_sequence[device_use_sequences[index]])

    # 对每一种可能的拿取顺序进行遍历
    # 这里map是为了把itertools.permutations生成的元组里的子元组都转化成子列表，以便传参
    ret_sequence = list()
    min_item_take_device_use_sequence = list()
    for one_item_take_sequence in map(list, itertools.permutations([0, 1, 2, 3, 4, 5])):
        # 初始化
        total_angles_list = list()
        if one_item_take_sequence == [2,3,5,4,0,1]:
            pass
        # 对可能的使用顺序进行计算
        possible_device_use_sequences = verify_feasibility(one_item_layout_sequence,
                                                           one_device_layout_sequence,
                                                           one_item_take_sequence)
        # 如果没有可能的，那么进行下一个拿取顺序的尝试
        if len(possible_device_use_sequences) == 0:
            continue
        # 对每一个可能的device使用顺序尝试
        for device_use_sequences in possible_device_use_sequences:
            # 初始化
            # 第一次转到0度
            total_angles = abs(calc_angle(0) - 320)
            spin_times = 1
            for i in range(5):
                # 加上每一次要转的角度
                total_angles += abs(calc_angle(i+1) - calc_angle(i))
                spin_times += 1 if calc_angle(i+1)-calc_angle(i) != 0 else 0
            device_use_sequences.append([total_angles, spin_times])
            device_use_sequences.append([calc_angle(i) for i in range(6)])

        # 下面进行这一次item_take_sequence最小角度的记录
        # 找到最小的角度以及转的最小的次数
        possible_device_use_sequences.sort(key=lambda x: x[6][1])
        possible_device_use_sequences.sort(key=lambda x: (x[6][1], x[6][0]))
        min_item_take_device_use_sequence.append(
            [one_item_take_sequence, possible_device_use_sequences[0]])

    min_item_take_device_use_sequence.sort(key=lambda x: x[1][6][1])
    min_item_take_device_use_sequence.sort(
        key=lambda x: (x[1][6][1], x[1][6][0]))
    try:
        a = min_item_take_device_use_sequence[0]
    except:
        pass
    return min_item_take_device_use_sequence[0]


# calc_min(one_item_layout_sequence);
for item_layout_sequence in all_item_layout_sequence:
    print("item_layout_sequence:", end='')
    ls = [item.cola_0_box_1 for item in item_layout_sequence]
    if ls == [1,0,0,1,0,1]:
        pass
    min_result = calc_min(item_layout_sequence)
    print(ls,end = ' ')
    print("device_use_sequence:" +
          str([min_result[1][i] for i in range(6)]), end=' ')
    print("item_take_sequence:"+str(min_result[0]), end=' ')
    print("angles:" + str(min_result[1][7]), end=' ')
    print("total angle:" + str(min_result[1][6][0]), end=' ')
    print("spin times:" + str(min_result[1][6][1]))
