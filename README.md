# drishya_vastu - ImageEngine

**ImageEngine** is a Python image processing library that integrates with C++ for high-performance operations. Note: C++ binaries are not included and need to be compiled.

## Features

- **Grayscale Conversion:** Convert RGB images to grayscale.
- **Brightness Adjustment:** Adjust brightness for red, green, and blue channels.
- **Contrast Adjustment:** Enhance or reduce contrast.
- **Channel Extraction:** Extract specific color channels (Red, Green, Blue).
- **Maximum Channel Preservation:** Preserve the maximum intensity channel.
- **Sobel Edge Detection:** Detect edges using the Sobel operator.
- **Image Display:** Display images directly.
- **Image Rotation:** Rotate images by specified degrees.
- **Image Cropping:** Crop images to specified dimensions.

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/ImageEngine.git
    ```

2. Compile the C++ binaries in the `utility` directory:

    ```bash
    g++ -shared -o rbg2grey.so rbg2grey.cpp
    g++ -shared -o brighten.so brighten.cpp
    g++ -shared -o contrast.so contrast.cpp
    g++ -shared -o channel_extraction.so channel_extraction.cpp
    g++ -shared -o keepmaxchannel.so keepmaxchannel.cpp
    g++ -shared -o sobel_edge.so sobel_edge.cpp
    g++ -shared -o rotate.so rotate.cpp
    g++ -shared -o crop.so crop.cpp
    ```

3. Install dependencies:

    ```bash
    pip install numpy
    ```

## Usage

Import and use ImageEngine in your Python scripts:

```python
from imageengine import ImageEngine

engine = ImageEngine()
grey_image = engine.grey_scale(image_data, height, width)
```

The name is derived from sanskrit where:<br>
-> drishya is translated as image<br>
-> vaastu is translated as architecture



<p align="center">
  
![3](https://github.com/user-attachments/assets/d461c858-02ac-4437-87b2-03e5f8f9cb49)
<br>
<br>
![Untitled-2](https://github.com/user-attachments/assets/ecd71eb9-03cc-40b1-8807-eb68bc5508d3)

</p>
