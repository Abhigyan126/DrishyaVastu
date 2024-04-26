#include <iostream>
#include "image_utils.h"

extern "C" {
    int* Brighten(int* data, int height, int width, int channels, int per_r, int per_g, int per_b) {
        // Reconstruct the 3D image array from the flattened array
        int*** image = ImageUtils::unflatten_image(data, height, width, channels);
        image = ImageUtils::brightness(image, height, width, channels, per_r, per_g, per_b);
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
