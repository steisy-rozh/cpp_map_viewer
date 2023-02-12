import sys
import os
from PIL import Image
from itertools import product

class InvalidImageException(Exception):
    "Could not open an image"
    pass

class InvalidQualityException(Exception):
    "Quality must be ge 1 and le 100"
    pass

class MyImage :
    def __init__(self, im: Image, type: str):
        self.type = type
        self.im = im
        self.width, self.height = im.size

    def split(self, width, height) :
        x_stop = self.width - self.width%width
        y_stop = self.height - self.height%height
        tiles = product(
            range(0, y_stop, height),
            range(0, x_stop, width)
        );

        for i, j in tiles:
            box = (j, i, j+width, i+height)
            img = self.im.crop(box)
            yield MyImage(img, self.type)

    def save(self, name: str, qual: int = 100):
        print(f'target quality is {qual}')

        if 1 > qual or qual > 100:
            raise InvalidQualityException

        self.im.save(f"{name}.{self.type}", quality=qual)


def open_image(filename) -> MyImage :
    try:
            im = Image.open(filename)
            print(f"an image has {im.size[0]}*{im.size[1]} size")
            return MyImage(im, 'jpg')
    except OSError:
        raise InvalidImageException(f'cannot open image {filename}')

def main():
    imagename = sys.argv[1]
    count = int(sys.argv[2])

    quality = 100 if count**2 > 100 else count**2

    directory_name = f'images_{count}'

    if not os.path.exists(directory_name):
        os.mkdir(directory_name)

    try:
        image = open_image(imagename)
        print(f'the image by path {imagename} is opened')

        tile_width = image.width // count
        tile_height = image.height // count
        print(f'the image will be splitted on {count * count} pieces')
        tile_images = image.split(tile_width, tile_height)

        for index, im in enumerate(tile_images):
            print(f"print {index+1} piece of image")
            im.save(f'{directory_name}/image_{index}', quality)

    except InvalidImageException as error:
        print('image exception:', error)


if __name__ == "__main__":
    main()