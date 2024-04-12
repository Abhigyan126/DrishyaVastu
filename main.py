import ctypes
import cv2
from arrtransform import ArrayDimentionTransform
import numpy

art = ArrayDimentionTransform()
# Load the shared library
add_lib = ctypes.CDLL('./print3d.so')  # Use the correct path to the shared library

# Define the argument and return types for the function
add_lib.PrintArray.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int]
add_lib.PrintArray.restype = ctypes.POINTER(ctypes.c_int)  # Adjusted return type

# Create a Python list
data = cv2.imread("/Users/abhigyan/Downloads/Library/download (1).png")  # Flattened 3D array
data = cv2.resize(data, (3,3))
data = art.flatten_image(data)
print(data)
# Convert the list to a C-style array
data_array = (ctypes.c_int * len(data))(*data)

# Dimensions of the original array
height = 3
width = 3
channels = 3  # Since the array is flattened, it's treated as a 1-channel image

# Call the C++ function from Python
result_ptr = add_lib.PrintArray(data_array, height, width, channels)

# Convert the returned pointer to a Python list
result = [result_ptr[i] for i in range(height * width * channels)]
print(result)
