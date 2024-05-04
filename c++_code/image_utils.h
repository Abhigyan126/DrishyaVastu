// image_utils.h
#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

class ImageUtils {
public:
    static int*** unflatten_image(int* flattened_image, int height, int width, int channels);
    static int* flatten_image(int*** threedimage, int height, int width, int channels);
    static int*** grey_scal(int*** data, int height, int width, int channels);
    static int*** brightness(int*** data, int height, int width, int channels, int per_r, int per_g, int per_b);
    static int*** contrast(int*** data, int height, int width, int channels, float rate);
    static int*** channel_extraction(int*** data, int height, int width, int channels, int ext_chanel);
    static int*** keep_max_channel(int*** data, int height, int width, int channels);
    static int*** merge_images(int*** image1, int height1, int width1, int*** image2, int height2, int width2, int channels);
    static int*** sobel_edge_detection(int*** data, int height, int width, int channels);

};
#endif
