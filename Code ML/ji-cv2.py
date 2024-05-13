import cv2
import jetson.inference
import jetson.utils

net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold = 0.5)
camera = jetson.utils.gstCamera(640, 360, "/dev/video0")
display = jetson.utils.glDisplay()

while display.IsOpen():
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    img, width, height = camera.CaptureRGBA()
    detections = net.Detect(img, width, height)
    display.RenderOnce(img, width, height)

    cv2.imshow('hello', img)

cv2.destroyAllWindows()