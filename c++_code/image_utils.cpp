// image_utils.cpp
#include<iostream>
#include<cmath>
#include "image_utils.h"
#include "ganit.hpp"

int*** allocate_3d_array(int height, int width, int channels) {
    int*** array = new int**[height];
    for (int i = 0; i < height; ++i) {
        array[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            array[i][j] = new int[channels];
        }
    }
    return array;

}

void delocate_3d_array(int*** array, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete[] array[i][j];
        }
        delete[] array[i];
    }
    delete[] array;
}

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
int*** ImageUtils::sobel_edge_detection(int*** data, int height, int width, int channels) {
    int*** edges = new int**[height];
    for (int i = 0; i < height; ++i) {
        edges[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            edges[i][j] = new int[channels];
            for (int c = 0; c < channels; ++c) {
                edges[i][j][c] = 0;
            }
        }
    }

    int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            for (int c = 0; c < channels; ++c) {
                int gx = 0;
                int gy = 0;
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        gx += data[i + k][j + l][c] * sobel_x[k + 1][l + 1];
                        gy += data[i + k][j + l][c] * sobel_y[k + 1][l + 1];
                    }
                }
                edges[i][j][c] = std::min(255, std::max(0, static_cast<int>(sqrt(gx * gx + gy * gy))));
            }
        }
    }

    return edges;
}

int*** ImageUtils::rotate(int*** data, int height, int width, int channels, int degree) {
    double radians = ganit::to_radians(degree);
    double cos = ganit::cos(radians);
    double sin = ganit::sin(radians);
    int new_height = static_cast<int>(ganit::fabs(height*cos) + ganit::fabs(width*sin));
    int new_width = static_cast<int>(ganit::fabs(height*sin) + ganit::fabs(width*cos));
    int*** rotated = allocate_3d_array(new_height, new_width, channels);
    
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            for (int c = 0; c < channels; ++c) {
                rotated[i][j][c] = 0;
            }
        }
    }

    int cx_old = width / 2;
    int cy_old = height / 2;
    int cx_new = new_width / 2;
    int cy_new = new_height / 2;

    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            int x_old = static_cast<int>((j - cx_new) * cos + (i - cy_new) * sin + cx_old);
            int y_old = static_cast<int>(-(j - cx_new) * sin + (i - cy_new) * cos + cy_old);

            // Check if the coordinates are within the bounds of the original image
            if (x_old >= 0 && x_old < width && y_old >= 0 && y_old < height) {
                for (int c = 0; c < channels; ++c) {
                    rotated[i][j][c] = data[y_old][x_old][c];
                }
            }
        }
    }

    return rotated;

}
