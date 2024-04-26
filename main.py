from ImageEngine import ImageEngine
import cv2
import numpy
engine = ImageEngine(debug=True)

data = cv2.imread("sample_640×426.ppm")
height = 426
width = 640
channels = 3
per_r = -100
per_g = -100
per_b = 0

data = engine.brightness(data, height, width, per_r, per_g, per_b, channels=3)
data = numpy.array(data)
cv2.imwrite("result.png", data, params=None)
