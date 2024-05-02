// image_utils.cpp
#include<iostream>
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

int*** ImageUtils::grey_scal(int*** data, int height, int width, int channels) {
    for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                // Calculate grayscale intensity
                int grayscale = 0;
                for (int c = 0; c < channels; ++c) {
                    grayscale += data[i][j][c];
                }
                grayscale /= channels;

                // Assign grayscale intensity to a single channel
                for (int c = 0; c < channels; ++c) {
                    data[i][j][c] = grayscale;
                }
            }
        }
    return data;
}

int*** ImageUtils::brightness(int*** data, int height, int width, int channels, int per_r, int per_g, int per_b) {
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                data[i][j][0] = std::min(255, (int)(data[i][j][0] + data[i][j][0] * per_b / 100.0));
                data[i][j][1] = std::min(255, (int)(data[i][j][1] + data[i][j][1] * per_g / 100.0));
                data[i][j][2] = std::min(255, (int)(data[i][j][2] + data[i][j][2] * per_r / 100.0));
            }
        }
    return data;
}

int*** ImageUtils::contrast(int*** data, int height, int width, int channels, float rate) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            for(int k = 0; k < channels; k++) {
                float pixel = static_cast<float>(data[i][j][k]) / 255.0; 
                pixel = (pixel - 0.5) * rate + 0.5;
                if(pixel < 0.0) {
                    pixel = 0.0;
                }
                else if(pixel > 1.0) {
                    pixel = 1.0;
                }
                data[i][j][k] = static_cast<int>(pixel * 255.0); 
            }
        }
    }
    return data;
}

int*** ImageUtils::channel_extraction(int*** data, int height, int width, int channels, int ext_chanel) {
    for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int grayscale = 0;
                for (int c = 0; c < channels; ++c) {
                    grayscale += data[i][j][c];
                }
                grayscale /= channels;
                for (int c = 0; c < channels; ++c) {
                    if(c != ext_chanel){
                        data[i][j][c] = grayscale;
                    }
                }
            }
        }
    return data;
}
int*** ImageUtils::keep_max_channel(int*** data, int height, int width, int channels) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int max_val = data[i][j][0];
            int max_index = 0;
            for (int c = 1; c < channels; ++c) {
                if (data[i][j][c] > max_val) {
                    max_val = data[i][j][c];
                    max_index = c;
                }
            }
            for (int c = 0; c < channels; ++c) {
                if (c != max_index) {
                    data[i][j][c] = 0;
                }
            }
        }
    }
    return data;
}
int*** ImageUtils::merge_images(int*** image1, int height1, int width1, int*** image2, int height2, int width2, int channels) {
    int max_height = std::max(height1, height2);
    int max_width = std::max(width1, width2);

    int*** merged_image = new int**[max_height];
    for (int i = 0; i < max_height; ++i) {
        merged_image[i] = new int*[max_width];
        for (int j = 0; j < max_width; ++j) {
            merged_image[i][j] = new int[channels];
            for (int c = 0; c < channels; ++c) {
                int value1 = (i < height1 && j < width1) ? image1[i][j][c] : image2[i][j][c];
                int value2 = (i < height2 && j < width2) ? image2[i][j][c] : image1[i][j][c];
                merged_image[i][j][c] = value1 + value2;
                merged_image[i][j][c] = std::min(255, std::max(0, merged_image[i][j][c]));
            }
        }
    }
    return merged_image;
}


