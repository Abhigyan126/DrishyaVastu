from ImageEngine import ImageEngine
import cv2
import numpy
engine = ImageEngine(debug=True)

data = cv2.imread("sample_640×426.ppm")
height = 426
width = 640
channels = 3

data = engine.grey_scale(data, height, width, channels)
data = numpy.array(data)
cv2.imwrite("result.png", data, params=None)
