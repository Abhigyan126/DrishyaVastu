from ImageEngine import ImageEngine
import cv2
import numpy
engine = ImageEngine(debug=True)

data = cv2.imread("sample_640×426.ppm")
height = 426
width = 640
channels = 3
degree = 5
ext_channel = 0
top = 50
bottom = 100
left = 200
right = 300
data = engine.crop(data, height, width, top, bottom, left, right, channels)
data1 = numpy.array(data[0])
cv2.imwrite("result.png", data1, params=None)
height = data[1]
width = data[2]
engine.display(data[0], height, width, channels)
