from ImageEngine import ImageEngine
import cv2
import numpy
engine = ImageEngine(debug=True)

data = cv2.imread("img.jpg")
height = 720
width = 1280
channels = 3
ext_channel = 0

data = engine.keepmaxchannel(data, height, width, channels=3)
data = numpy.array(data)
cv2.imwrite("result.png", data, params=None)
