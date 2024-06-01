import ctypes
from arrtransform import ArrayDimentionTransform
import numpy as np
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
    def brightness(self, data, height, width, per_r, per_g, per_b, channels = 3):
        cfile = ctypes.CDLL('./brighten.so')
        cfile.Brighten.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.Brighten.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.Brighten(data_array, height, width, channels, per_r, per_g, per_b)
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        brighten = art.unflat_image(result, height, width, channels)
        if brighten and self.debug == True:
            print("Image generated")
        return brighten
    def contrast(self, data, height, width, rate, channels = 3):
        cfile = ctypes.CDLL('./contrast.so')
        cfile.contrast.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.contrast.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.contrast(data_array, height, width, channels, rate)
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        contrast = art.unflat_image(result, height, width, channels)
        if contrast and self.debug == True:
            print("Image generated")
        return contrast
    def channel_extract(self, data, height, width, ext_channel, channels =3):
        cfile = ctypes.CDLL('./channel_extraction.so')
        cfile.channel_extraction.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.channel_extraction.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.channel_extraction(data_array, height, width, channels, ext_channel)
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        channel_extracted = art.unflat_image(result, height, width, channels)
        if channel_extracted and self.debug == True:
            print("Image generated")
        return channel_extracted
    def keepmaxchannel(self, data, height, width, channels =3):
        cfile = ctypes.CDLL('./utility/keepmaxchannel.so')
        cfile.keep_max_channel.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.keep_max_channel.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.keep_max_channel(data_array, height, width, channels)
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        max_channel = art.unflat_image(result, height, width, channels)
        if max_channel and self.debug == True:
            print("Image generated")
        return max_channel
    def sobel_edge_detection(self, data, height, width, channels =3):
        cfile = ctypes.CDLL('./utility/sobel_edge.so')
        cfile.sobel_edge_detection.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.sobel_edge_detection.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.sobel_edge_detection(data_array, height, width, channels)
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        edge_image = art.unflat_image(result, height, width, channels)
        if edge_image and self.debug == True:
            print("Image generated")
        return edge_image
    def display(self, data, height, width, channels):
            flattened_data = art.flatten_image(data)
            data_array = (ctypes.c_int * len(flattened_data))(*flattened_data)
            lib = ctypes.CDLL('./libimage_display.dylib')
            lib.display_image.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int]
            lib.display_image(data_array, height, width, channels)
    def rotate(self, data, height, width, degree, channels =3):
        cfile = ctypes.CDLL('./rotate.so')
        cfile.rotate.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        cfile.rotate.restype = ctypes.POINTER(ctypes.c_int)
        data = art.flatten_image(data)
        data_array = (ctypes.c_int * len(data))(*data)
        result_ptr = cfile.rotate(data_array, height, width, channels, degree)
        result = [result_ptr[i] for i in range(height * width * channels)]
        if self.debug:
            print(result)
        rotate_image = art.unflat_image(result, height, width, channels)
        if rotate_image and self.debug == True:
            print("Image generated")
        return rotate_image
