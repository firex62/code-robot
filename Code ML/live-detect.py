import numpy as np
import cv2
import jetson.inference
import jetson.utils
from jetson_utils import (cudaAllocMapped, cudaConvertColor, 
                          cudaDeviceSynchronize, cudaToNumpy)

net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold = 0.5)
camera = jetson.utils.gstCamera(640, 360, "/dev/video0")
display = jetson.utils.glDisplay()

while display.IsOpen():
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
    display.RenderOnce(img, lebar, tinggi)
    display.SetTitle("Deteksi Objek {:.0f} FPS".format(net.GetNetworkFPS()))
    
    
    cv2.imshow('test', array)
    print(deteksi.confidence)
     
cv2.destroyAllWindows()