#include <iostream>
#include "image_utils.h"

using namespace std;

extern "C" {
    int* PrintArray(int* data, int height, int width, int channels) {
        // Reconstruct the 3D image array from the flattened array
        int*** image = ImageUtils::unflatten_image(data, height, width, channels);

        // Flatten the 3D image array back into a 1D array
        int* result = ImageUtils::flatten_image(image, height, width, channels);

        // Free memory allocated for the 3D array
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

int main() {
    return 0;
}
