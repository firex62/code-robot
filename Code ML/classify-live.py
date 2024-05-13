import sys
from jetson_inference import imageNet
from jetson_utils import videoSource, videoOutput, cudaFont, Log

# img = jetson.utils.loadImage("/home/kukulai/Downloads/bus.jpg")

net = imageNet("googlenet")

# class_idx, confidence = net.Classify(img)

# class_desc = net.GetClassDesc(class_idx)

# print("Terdeteksi '{:s}' (class #{:d}) confidence : {:f}%".format(class_desc, class_idx, confidence * 100))

vid = videoSource("/dev/video0", 1)
output = videoOutput("display://0", 1)
font = cudaFont()

while True:
    img = vid.Capture()
    if img is None: # timeout
        continue


    predictions = net.Classify(img, int(1))

    # draw predicted class labels
    for n, (classID, confidence) in enumerate(predictions):
        classLabel = net.GetClassLabel(classID)
        confidence *= 100.0

        print(f"imagenet:  {confidence:05.2f}% class #{classID} ({classLabel})")

        font.OverlayText(img, text=f"{confidence:05.2f}% {classLabel}", 
                         x=5, y=5 + n * (font.GetSize() + 5),
                         color=font.White, background=font.Gray40)


    output.Render(img)

    if not input.IsStreaming() or not output.IsStreaming():
        break