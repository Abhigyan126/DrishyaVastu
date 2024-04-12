#include <iostream>
#include "image_utils.h"

extern "C" {
    int* PrintArray(int* data, int height, int width, int channels) {
        // Reconstruct the 3D image array from the flattened array
        int*** image = ImageUtils::unflatten_image(data, height, width, channels);

        // Convert the image to grayscale
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                // Calculate grayscale intensity
                int grayscale = 0;
                for (int c = 0; c < channels; ++c) {
                    grayscale += image[i][j][c];
                }
                grayscale /= channels;

                // Assign grayscale intensity to a single channel
                for (int c = 0; c < channels; ++c) {
                    image[i][j][c] = grayscale;
                }
            }
        }
        channels = 1;
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
