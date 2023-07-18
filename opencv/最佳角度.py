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
            valid_device_use_sequence.append(device_use_sequence)
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
    # valid_device_use_sequences = [[2,3,4,5,0,1]]
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
            elif device.arm_index % 2 == 1:
                # 如果要拿的是前方摆放东西的0号位，那么不用考虑，肯定可以
                if item_take_sequence[index] == 0:
                    pass
                elif device_layout_sequence[device.arm_index-1].is_take == True and item_layout_sequence[item_take_sequence[index]-1].taken_device_index == -1:
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


angles_1_1 = [314, 350, 26, 60, 98, 134, 170]
angles_2_1 = [200, 232, 266, 302, 338, 14, 52]
angles_3_1 = [70, 108, 144, 178, 216, 252, 288]
center_angles = [122, 160, 160, 160, 160, 160, 160]

min_angles_list = list()
min_angle_sum = 0

device_take_angles = generate_device_take_angles()


all_item_layout_sequence = [generate_item_layout_sequence(ls) for ls in map(
    list, set(itertools.permutations([0, 0, 0, 1, 1, 1])))]
one_device_layout_sequence = generate_device_layout_sequence([
    1,1,1,0,0,0])
one_item_layout_sequence  = generate_item_layout_sequence([0,1,0,0,1,1])
# one_item_take_sequence = [0,1,2,3,4,5]





def calc_min(one_item_layout_sequence:list[ColaBox]):
    """
    参数：元素为ColaBox对象的列表
    """
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
    for one_item_take_sequence in map(list, itertools.permutations([0, 1, 2, 3, 4, 5])):
        # 初始化
        total_angles_list = list()
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
            # 假设不需要转到第一次拿取的角度，所以可以初始化为0
            total_angles = 0
            for i in range(5):
                # 加上每一次要转的角度
                total_angles += abs(calc_angle(i+1) - calc_angle(i))
            # 记录这一个device顺序的总角度
            total_angles_list.append(total_angles)

        ## 下面进行这一次item_take_sequence最小角度的记录
        # 找到最小的角度
        min_angle = min(total_angles_list)
        # 找到最小的device_use_sequences
        min_angle_device_use_sequences = possible_device_use_sequences[total_angles_list.index(
            min_angle)]
        # 把这一次的item_take_sequence记录到上面定义好的min_angles_list中以便后面找到所有item_take_sequence中最小的角度
        min_angles_list.append(
            [min_angle, min_angle_device_use_sequences, one_item_take_sequence])


    # 完成了所有item_take_sequence的遍历
    # 得到一个min_angles_list,记录了所有item_take_sequence中最小的角度以及相应的device_use_sequence和item_take_sequence
    min_result_list = min_sublist(min_angles_list)
    # TODO:注意下行代码是给center_servo_angles赋值，但是这个应该在arduino中补全
    # center_servo_angles = [angle(one_item_layout_sequence[min_result_list[2][i]], one_device_layout_sequence[min_result_list[1][i]])for i in range(6)]

    return min_result_list[1], min_result_list[2]

# calc_min(one_item_layout_sequence);
# for item_layout_sequence in all_item_layout_sequence:
#     for i in range(6):
#         print(item_layout_sequence[i].cola_0_box_1,end='')
#     print(calc_min(item_layout_sequence))
