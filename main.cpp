// main.cpp
#include <iostream>
#include "image_utils.h"

int main() {
    // Example usage:
    // Create a sample flattened array
    int flattened_image[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Dimensions of the original image
    int height = 2;
    int width = 2;
    int channels = 3;

    // Reconstruct the image
    int*** reconstructed_image = ImageUtils::unflatten_image(flattened_image, height, width, channels);

    // Print the reconstructed image
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < channels; ++k) {
                std::cout << reconstructed_image[i][j][k] << " ";
            }
        }
        std::cout << std::endl;
    }

    // Don't forget to delete the allocated memory
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete[] reconstructed_image[i][j];
        }
        delete[] reconstructed_image[i];
    }
    delete[] reconstructed_image;

    return 0;
}
