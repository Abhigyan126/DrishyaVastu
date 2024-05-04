from ImageEngine import ImageEngine
import cv2
import numpy
engine = ImageEngine(debug=True)

data = cv2.imread("result.png")
height = 426
width = 640
channels = 1
ext_channel = 0
data = engine.sobel_edge_detection(data, height, width, channels=3)
data = numpy.array(data)
cv2.imwrite("result.png", data, params=None)
