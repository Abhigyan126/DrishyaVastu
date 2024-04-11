class ArrayDimentionTransform:
    def __init__(self, has_version=False) -> None:
        self.version = 1.0 if has_version else None

    def flatten_image(self, arr):
        """
        Flatten a 3D image array into a 1D array.

        Parameters:
        - arr: list of lists of lists, a 3D array representing an image.

        Returns:
        - flattened_image: list, a 1D array representing the flattened image.
        """
        flat = []
        for row in arr:
            for col in row:
                flat.extend(col)
        return flat

    def unflat_image(self, arr, width, height, channels):
        """
        Reconstruct a flattened 1D image array back into a 3D image array.

        Parameters:
        - arr: list, a 1D array representing a flattened image.
        - height: int, height of the original image.
        - width: int, width of the original image.
        - channels: int, number of channels in the original image.

        Returns:
        - image: list of lists of lists, a 3D array representing the reconstructed image.
        """
        unflat = []
        for i in range(height):
            row = []
            for j in range(width):
                pixel = arr[(i * width + j) * channels : (i * width + j + 1) * channels]
                row.append(pixel)
            unflat.append(row)
        return unflat 

    def __version__(self):
        if self.version:
            print(self.version)
