#include <iostream>
#include "image_utils.h"

extern "C" {
    int* merge(int* data1, int height1, int width1, int* data2, int height2, int width2, int channels) {
        int*** image1 = ImageUtils::unflatten_image(data1, height1, width1, channels);
        int*** image2 = ImageUtils::unflatten_image(data2, height2, width2, channels);
        int max_height = std::max(height1, height2);
        int max_width = std::max(width1, width2);
        int*** merged_image = ImageUtils::merge_images(image1, height1, width1, image2, height2, width2, channels);
        int* result = ImageUtils::flatten_image(merged_image, max_height, max_width, channels);

        for (int i = 0; i < max_height; ++i) {
            for (int j = 0; j < max_width; ++j) {
                delete[] merged_image[i][j];
            }
            delete[] merged_image[i];
        }
        delete[] merged_image;

        return result;
    }
}
