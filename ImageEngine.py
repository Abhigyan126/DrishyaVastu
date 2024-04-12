import ctypes
from arrtransform import ArrayDimentionTransform
art = ArrayDimentionTransform()

class ImageEngine():
    def __init__(self, debug = False) -> None:
        self.debug = debug
    def grey_scale(self, data, height, width, channels =3):
        cfile = ctypes.CDLL('./utility/rbg2grey.so')
        cfile.GreyScaling.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.GreyScaling.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.GreyScaling(data_array, height, width, channels)
        channels = 1
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        grey_image = art.unflat_image(result, height, width, channels)
        if grey_image and self.debug == True:
            print("Image generated")
        return grey_image

