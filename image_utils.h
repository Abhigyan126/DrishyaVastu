// image_utils.h
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

class ImageUtils {
public:
    static int*** unflatten_image(int* flattened_image, int height, int width, int channels);
    static int* flatten_image(int*** threedimage, int height, int width, int channels);
};

#endif
