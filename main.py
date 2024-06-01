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

data = engine.rotate(data, height, width,degree, channels)

#data1 = numpy.array(data)
#cv2.imwrite("result.png", data1, params=None)
engine.display(data, height, width, channels)
