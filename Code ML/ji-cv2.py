import cv2
import jetson.inference
import jetson.utils

#net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold = 0.5)
net = jetson.inference.detectNet(argv=['--input-blob=input_0', '--model=/home/kukulai/Downloads/model/detect-sampah3/ssd-mobilenet.onnx', '--output-cvg=scores', '--output-bbox=boxes', '--labels=/home/kukulai/Downloads/model/detect-sampah3/labels.txt', '--overlay=lines,labels,conf'],threshold = 0.5)
camera = jetson.utils.gstCamera(640, 360, "/dev/video0")
display = jetson.utils.glDisplay()

while display.IsOpen():
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    img, width, height = camera.CaptureRGBA()
    detections = net.Detect(img, width, height)
    display.RenderOnce(img, width, height)

    for det in detections:
        print(det.ClassID)
        print(det.Center)

    # cv2.imshow('hello', img)

cv2.destroyAllWindows()