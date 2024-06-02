#include <iostream>
#include "image_utils.h"

extern "C" {
    int* crop(int* data, int height, int width, int channels, int top, int bottom, int left, int right) {
        // Reconstruct the 3D image array from the flattened array
        int*** image = ImageUtils::unflatten_image(data, height, width, channels);
        image = ImageUtils::crop(image, height, width, channels, top, bottom, left, right);
        height = bottom - top + 1;
        width = right - left + 1;
        int* result = ImageUtils::flatten_image(image, height, width, channels);

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete[] image[i][j];
            }
            delete[] image[i];
        }
        delete[] image;

        return result;
    }
}
