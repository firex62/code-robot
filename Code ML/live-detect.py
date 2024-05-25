import numpy as np
import cv2
import jetson.inference
import jetson.utils
from jetson_utils import (cudaAllocMapped, cudaConvertColor, 
                          cudaDeviceSynchronize, cudaToNumpy)

# net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold = 0.5)
net = jetson.inference.detectNet(argv=['--input-blob=input_0', '--model=/home/kukulai/Downloads/model/detect-sampah3/ssd-mobilenet.onnx', '--output-cvg=scores', '--output-bbox=boxes', '--labels=/home/kukulai/Downloads/model/detect-sampah3/labels.txt', '--overlay=lines,labels,conf'],threshold = 0.5)
camera = jetson.utils.gstCamera(640, 360, "/dev/video0")
display = jetson.utils.glDisplay()

while True:
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    img, lebar, tinggi = camera.CaptureRGBA()
    
    bgr_img = cudaAllocMapped(width=img.width,
                          height=img.height,
						  format='bgr8')
    
    cudaConvertColor(img, bgr_img)
    
    cudaDeviceSynchronize()
    
    array = cudaToNumpy(bgr_img)
    
    cudaDeviceSynchronize()
    deteksi = net.Detect(img, lebar, tinggi)
    # display.RenderOnce(img, lebar, tinggi)
    # display.SetTitle("Deteksi Objek {:.0f} FPS".format(net.GetNetworkFPS()))
    
    
    # for index, det in enumerate(deteksi):
    #     print(index)
        # print(type(det.Top))
        # label = net.GetClassLabel(det.ClassID)
        # label2 = label + " " + str(det.ClassID)
        # print(label)
        # cv2.rectangle(array, (int(det.Left), int(det.Top)), (int(det.Right), int(det.Bottom)), (255,0,0),)
        # cv2.putText(array, label2, (int(det.Left), int(det.Top)), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2) 
    #     cv2.rectangle(array, )
        # print(det)
    if deteksi:
        objek1 = deteksi[0]
        # print(type(det.Top))
        label = net.GetClassLabel(objek1.ClassID)
        cv2.rectangle(array, (int(objek1.Left), int(objek1.Top)), (int(objek1.Right), int(objek1.Bottom)), (255,0,0),)
        cv2.putText(array, label, (int(objek1.Left), int(objek1.Top)), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)


    cv2.imshow('test', array)
    # print(deteksi.confidence)
     
cv2.destroyAllWindows()