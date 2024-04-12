// image_utils.cpp
#include "image_utils.h"

int*** ImageUtils::unflatten_image(int* flattened_image, int height, int width, int channels) {
    int*** image = new int**[height];
    for (int i = 0; i < height; ++i) {
        image[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            image[i][j] = new int[channels];
            for (int k = 0; k < channels; ++k) {
                image[i][j][k] = flattened_image[i * width * channels + j * channels + k];
            }
        }
    }
    return image;
}

int* ImageUtils::flatten_image(int*** threedimage, int height, int width, int channels) {
    int total_elements = height * width * channels;

    int* flattened_image = new int[total_elements];

    int index = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < channels; ++k) {
                flattened_image[index++] = threedimage[i][j][k];
            }
        }
    }

    return flattened_image;
}
