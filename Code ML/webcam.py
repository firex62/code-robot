import cv2
import numpy as np
#import jetson.inference
import jetson.utils
from jetson_utils import cudaToNumpy


# camera = jetson.utils.gstCamera(640, 360, "/dev/video0")
#net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold = 0.5)
vid = cv2.VideoCapture(0)
#display = jetson.utils.glDisplay()

while True:
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    
    ret, frame = vid.read()
    frame_crop = frame[80:360, 120:470]

    #frame2 = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)

    #tinggi, lebar, _ = frame.shape
    
    #deteksi = net.Detect(frame2, lebar, tinggi)

    #display.RenderOnce(img, lebar, tinggi)

    #cv2.imshow('frame RGBA', frame2)
    
    print(type(frame))
    print(frame.shape)
    print(frame.dtype)

    cv2.imshow('adsfasf', frame)
    cv2.imshow('adsfasff', frame_crop)

vid.release()
cv2.destroyAllWindows()