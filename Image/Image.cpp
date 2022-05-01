#include "Filters.h"
#include "Image.h"


Pixel::Pixel() : red(0), green(0), blue(0) {
}

Pixel::Pixel(float red, float green, float blue) : red(red), green(green), blue(blue) {
}

Pixel& Pixel::operator=(Pixel const& pixel) {
    this->red = pixel.red;
    this->green = pixel.green;
    this->blue = pixel.blue;

    return *this;
}

Pixel& Pixel::operator*=(Pixel const& pixel) {
    this->red *= pixel.red;
    this->green *= pixel.green;
    this->blue *= pixel.blue;

    return *this;
}

Pixel& Pixel::operator*=(float value) {
    this->red *= value;
    this->green *= value;
    this->blue *= value;

    return *this;
}

Pixel& Pixel::operator+=(Pixel const& pixel) {
    this->red += pixel.red;
    this->green += pixel.green;
    this->blue += pixel.blue;

    return *this;
}

bool Pixel::operator==(Pixel const& pixel) {
    if (red == pixel.red && green == pixel.green && blue == pixel.blue) {
        return true;
    }

    return false;
}

bool Pixel::operator!=(Pixel const& pixel) {
    return !(*this == pixel);
}

Image::Image() : width(0), height(0) {
}

Image::Image(int width, int height) : width(width), height(height), pixels(std::vector<std::vector<Pixel>>(width, std::vector<Pixel>(height, {0, 0, 0}))) {
}

Pixel Image::GetColor(int x, int y) const {
    if (((x >= 0 && x < this->height && y >= 0 && y < this->width))) {
        return pixels[x][y];
    }
}

void Image::SetColor(const Pixel& pixel, int x, int y) {
    pixels[x][y].red = pixel.red;
    pixels[x][y].green = pixel.green;
    pixels[x][y].blue = pixel.blue;
}

Image& Image::Copy(const Image& im) {
    this->width = im.width;
    this->height = im.height;
    this->pixels = (std::vector<std::vector<Pixel>>(width, std::vector<Pixel>(height, {0, 0, 0})));
    for (size_t y = 0; y < im.height; ++y) {
        for (size_t x = 0; x < im.width; ++x) {
            pixels[x][y] = im.pixels[x][y];
        }
    }

    return *this;
}

Image& Image::operator=(const Image &im) {
    this->Copy(im);

    return *this;
}

bool Image::operator==(const Image &im) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; y < width; ++x) {
            if (this->GetColor(x, y) != im.GetColor(x, y)) {
                return false;
            }
        }
    }

    return true;
}

bool Image::ImageExists(const Image &im, int x, int y) {
    if ((x >= 0 && x < im.height) && (y >= 0 && y < im.width)) {
        return true;
    }

    return false;
}
