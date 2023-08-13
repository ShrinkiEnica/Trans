import sensor, image, time
from pyb import UART
uart = UART(3, 9600)


cola_threshold = (25, 89, 23, 75, -18, 31)

# regions of interest
# 单位为x,y,w,h
roi_1 = (0,100,40,100)
roi_2 = (60,80,40,100)
roi_3 = (110,60,40,100)
roi_4 = (170, 60, 40,100)
roi_5 = (220,80,40,100)
roi_6 = (270,100,40,100)
rois = (roi_1, roi_2, roi_3,roi_4, roi_5,roi_6)
cola_box_list = [1,1,1,1,1,1]

sensor.reset()
# 关闭自动自动增益。默认开启的，在颜色识别中，一定要关闭白平衡。
sensor.set_auto_gain(False)
#关闭白平衡。白平衡是默认开启的，在颜色识别中，一定要关闭白平衡。
sensor.set_auto_whitebal(False)
sensor.set_pixformat(sensor.RGB565)
# 分辨率为320x240
sensor.set_framesize(sensor.QVGA)
# 等待感光器件稳定，跳过一些帧
sensor.skip_frames(time = 2000)
clock = time.clock()

while(True):
        clock.tick() # Track elapsed milliseconds between snapshots().
        img = sensor.snapshot() # 从感光芯片获得一张图像
        for i in range(6):
            img.draw_rectangle(rois[i])
        for i in range(6):
            blob = img.find_blobs([cola_threshold],roi = rois[i], x_stride = 4, y_stride = 5,pixels_threshold = 30)
            print(blob)
            if (len(blob) == 0):
                cola_box_list[i] = 0
            time.sleep(1)
        print("fps:",end='')
        print(clock.fps()) # 注意: 你的OpenMV连到电脑后帧率大概为原来的一半
        print(f"cola_box_list{cola_box_list}")
        #如果断开电脑，帧率会增加
        # 如果可乐有三个那么退出循环
        img.save("a.jpg")
        time.sleep_ms(100)
        if cola_box_list.count(0)==3:
            break



while(True):
    uart.write("s")
    for i in range(6):
        uart.write(str(cola_box_list[i]).encode())
        time.sleep_ms(10)
