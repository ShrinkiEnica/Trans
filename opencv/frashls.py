#coding = UTF-8
import cv2
import numpy as np
import matplotlib.pyplot as plt

name = 0

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
 
 
while(1):
        ret,frame = cap.read()
        img_bgr = img_p(frame)
        cv2.imshow('img_bgr', img_bgr)
        cv2.waitKey(1)

        img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
        img_hls = cv2.cvtColor(img_rgb, cv2.COLOR_RGB2HLS)

        low_threshold = np.array([0, 200, 0], dtype=np.uint8)
        high_threshold = np.array([180, 255, 255], dtype=np.uint8)
        mask = cv2.inRange(img_hls, low_threshold, high_threshold)
        white_parts = cv2.bitwise_and(img_rgb, img_rgb, mask = mask)
        blur = cv2.GaussianBlur(white_parts, (7,7), 0)

        cv2.imshow('img_hls', img_hls)
        cv2.waitKey(1)
        #plt.imshow(blur)
        #plt.show()


        k = cv2.waitKey(1)
        if (k == ord('q')):
            break
        '''
        elif(k == ord('s')):
                #name = input('name:')
                name += 1
                #filename = r'./camera/' + str(name) + '.jpg'
                filename = str(name) + '.jpg'
                cv2.imwrite(filename, img)
                print(filename)
                #break 
        '''
cap.release()
cv2.destroyAllWindows()
