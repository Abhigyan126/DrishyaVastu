from ImageEngine import ImageEngine
import cv2
import numpy
engine = ImageEngine(debug=True)

data = cv2.imread("image.jpg")
height = 64
width = 100
channels = 3
ext_channel = 0

data = engine.keepmaxchannel(data, height, width, channels)

data = engine.display(data, height, width, channels)

"""
data = numpy.array(data)
cv2.imwrite("result.png", data, params=None)
"""