#include <iostream>
#include "image_utils.h"

extern "C" {
    int* keep_max_channel(int* data, int height, int width, int channels) {
        int*** image = ImageUtils::unflatten_image(data, height, width, channels);
        image = ImageUtils::keep_max_channel(image, height, width, channels);
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
