import jetson.inference
import jetson.utils

img = jetson.utils.loadImage("/home/kukulai/Downloads/bus.jpg")

net = jetson.inference.imageNet("googlenet")

class_idx, confidence = net.Classify(img)

class_desc = net.GetClassDesc(class_idx)

print("Terdeteksi '{:s}' (class #{:d}) confidence : {:f}%".format(class_desc, class_idx, confidence * 100))