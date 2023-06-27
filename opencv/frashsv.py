#coding = UTF-8
import cv2
import numpy as np
import matplotlib.pyplot as plt
import serial
import time



#name = 0
port = "/dev/ttyACM0"
baudRate = 9600

ser = serial.Serial(port,baudRate,timeout = 0.5)

cap = cv2.VideoCapture(0)  
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M', 'J', 'P', 'G'))  

ret, frame = cap.read()
rows, cols, channels = frame.shape
#print(cols, rows, channels)
 
def img_p(img):
    blur = cv2.blur(img, (3,3))
    b = 50
    pts1 = np.float32([[b, 0], [cols-b, 0], [0, rows], [cols, rows]])
    pts2 = np.float32([[0, 0], [cols, 0], [0, rows], [cols, rows]])

    M = cv2.getPerspectiveTransform(pts1, pts2)
    dst = cv2.warpPerspective(blur, M, (cols, rows))
 
    return dst
 
a,b,c,d,e,f = '0','0','0','0','0','0'

#for i in range(0,10):
while (1):
        ret,frame = cap.read()
        img_bgr = img_p(frame)
        #cv2.imshow('img_bgr', img_bgr)
        #cv2.waitKey(1)

        img_hsv = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2HSV)

        lower_red = np.array([160,100,50])
        upper_red = np.array([180,255,255])
        mask = cv2.inRange(img_hsv,lower_red, upper_red)

        cv2.imshow('img_mask', mask)
        cv2.waitKey(1)

        contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        #max = 0
        font = cv2.FONT_HERSHEY_SIMPLEX
        for idx,contour in enumerate(contours):
        #for c in range(len(contours)):
            area = cv2.contourArea(contour)
            if len(contour) < 5:
                continue
            if area < 1000:
                continue
            #if area > max:
            #    max = area
            #perimeter = cv2.arcLength(contour,True)  
            #approx = cv2.approxPolyDP(contour,0.02*perimeter,True)
            #CornerNum = len(approx)
            #print(CornerNum)
            #if idx >= 0 & CornerNum < 16:
            if idx >= 0:
                x, y, w, h = cv2.boundingRect(contour)
                cv2.rectangle(img_bgr, (x, y), (x + w, y + h), (0, 255, 0), 2)
                cv2.putText(img_bgr,"Coco(%d,%d)"%(x,y),(x, y), font, 1.2, (0, 0, 255), 2)
                if ((x + w / 2) >0) & ((x + w / 2) < 106.6):
                    a = '1'
                if ((x + w / 2) >107) & ((x + w / 2) < 214):
                    b = '1'
                if ((x + w / 2) >214) & ((x + w / 2) < 320):
                    c = '1'
                if ((x + w / 2) >320) & ((x + w / 2) < 427):
                    d = '1'
                if ((x + w / 2) >427) & ((x + w / 2) < 534):
                    e = '1'
                if ((x + w / 2) >534) & ((x + w / 2) < 640):
                    f = '1'
        cv2.imshow("Done", img_bgr)
        k = cv2.waitKey(1)

        #if (k == ord('q')):
        #    break

#ser.flushInput()
time.sleep(1.6)

print("%d%d%d%d%d%d"%(a,b,c,d,e,f))
ser.write('s'.encode())
ser.write(a.encode())
ser.write(b.encode())
ser.write(c.encode())
ser.write(d.encode())
ser.write(e.encode())
ser.write(f.encode())
response = ser.readall()
print(response)
#ser.flushInput()

ser.close()
cap.release()
cv2.destroyAllWindows()
