#include <iostream>
#include "image_utils.h"

extern "C" {
    int* sobel_edge_detection(int* data, int height, int width, int channels) {
        // Reconstruct the 3D image array from the flattened array
        int*** image = ImageUtils::unflatten_image(data, height, width, channels);
        image = ImageUtils::sobel_edge_detection(image, height, width, channels);
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
