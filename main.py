import ctypes

# Load the shared library
add_lib = ctypes.CDLL('./add.so')  # Use the correct path to the shared library

# Define the argument and return types for the function
add_lib.printArray.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int]
add_lib.printArray.restype = ctypes.c_bool

# Create a Python list
data = [1, 2, 3, 1, 2, 0]  # Flattened 3D array

# Convert the list to a C-style array
data_array = (ctypes.c_int * len(data))(*data)

# Dimensions of the original array
height = 2
width = 3
channels = 1  # Since the array is flattened, it's treated as a 1-channel image

# Call the C++ function from Python
result = add_lib.printArray(data_array, height, width, channels)

# Check if the function call was successful
if result:
    print("Array printed successfully")
else:
    print("Failed to print array")
