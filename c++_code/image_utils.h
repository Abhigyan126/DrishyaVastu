// image_utils.h
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

class ImageUtils {
public:
    static int*** unflatten_image(int* flattened_image, int height, int width, int channels);
    static int* flatten_image(int*** threedimage, int height, int width, int channels);
    static int*** grey_scal(int*** data, int height, int width, int channels);
    static int*** brightness(int*** data, int height, int width, int channels, int per_r, int per_g, int per_b);
    static int*** contrast(int*** data, int height, int width, int channels, float rate);



};

#endif
