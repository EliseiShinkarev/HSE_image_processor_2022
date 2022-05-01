#include "Filters.h"
#include "Image.h"

#include <cmath>
#include <iostream>

Pixel FindTheNearestPixel(int i, int j, Image& copy_image) {
    if (i < 0 && j >= 0 && j < copy_image.height) {
        return copy_image.GetColor(i + 1, j);
    }
    if (j < 0 && i >= 0 && i < copy_image.width) {
        return copy_image.GetColor(i, j + 1);
    }
    if (j >= 0 && j < copy_image.height && i >= copy_image.width) {
        return copy_image.GetColor(i - 1, j);
    }
    if (j >= copy_image.height && i >= 0 && i < copy_image.width)  {
        return copy_image.GetColor(i, j - 1);
    }
    if (i < 0 && j < 0) {
        return copy_image.GetColor(i + 1, j + 1);
    }
    if (i < 0 && j >= copy_image.height) {
        return copy_image.GetColor(i + 1, j - 1);
    }
    if (j < 0 && i >= copy_image.width) {
        return copy_image.GetColor(i - 1, j + 1);
    }
    if (i >= copy_image.width && j >= copy_image.width) {
        return copy_image.GetColor(i - 1, j - 1);
    }
    return copy_image.GetColor(i, j);
}

void Filter::Convolution(Image& image, std::vector<std::vector<float>> matrix) {
    Image copy_image;
    copy_image.Copy(image);

    for (size_t y = 0; y < image.height; ++y) {
        for (size_t x = 0; x < image.width; ++x) {
            std::vector<std::vector<Pixel>> image_matrix(3, std::vector<Pixel>(3, {0, 0, 0}));

            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    if (x + i - 1 < 0 || x + i - 1 >= copy_image.width || y + j - 1 < 0 || y + j - 1 >= copy_image.height) {
                        image_matrix[i][j] = FindTheNearestPixel(x + i - 1, y + j - 1, copy_image);
                    } else if (x >= 0 && x < image.height && y >= 0 && y < image.width) {
                        image_matrix[i][j] = copy_image.GetColor(x + i - 1, y + j - 1);
                    }
                }
            }

            Pixel pixel;
            double tmp_red = 0;
            double tmp_green = 0;
            double tmp_blue = 0;

            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    tmp_red += matrix[i][j] * image_matrix[i][j].red;
                    tmp_green += matrix[i][j] * image_matrix[i][j].green;
                    tmp_blue += matrix[i][j] * image_matrix[i][j].blue;
                }
            }

            pixel.red = fmin(1, fmax(0, tmp_red));
            pixel.green = fmin(1, fmax(0, tmp_green));
            pixel.blue = fmin(1, fmax(0, tmp_blue));
            image.SetColor(pixel, x, y);
        }
    }
}

void Filter::Apply(Image& image) {
    std::cout << "Filter was applied\n";
}

void Grayscale::Apply(Image& image) {
    for (size_t y = 0; y < image.height; ++y) {
        for (size_t x = 0; x < image.width; ++x) {
            auto c = image.GetColor(x, y).red * 0.299 + image.GetColor(x, y).green * 0.587 + image.GetColor(x, y).blue * 0.114;
            Pixel pixel(c, c, c);
            image.SetColor(pixel, x, y);
        }
    }
    std::cout << "Grayscale was applied\n";
}

void Negative::Apply(Image& image) {
    for (size_t y = 0; y < image.height; ++y) {
        for (size_t x = 0; x < image.width; ++x) {
            image.SetColor(Pixel(1 - image.pixels[x][y].red, 1 - image.pixels[x][y].green, 1 - image.pixels[x][y].blue), x, y);
        }
    }
    std::cout << "Negative was applied\n";
}

void Sharpening::Apply(Image& image) {
    std::cout << "1\n";
    Convolution(image, {{0,-1, 0}, {-1, 5, -1}, {0, -1, 0}});
    std::cout << "Sharpering was applied\n";
}

EdgeDetection::EdgeDetection(int threshold) {
    this->tmp_threshold = threshold / 255.0;
}

void EdgeDetection::Apply(Image& image){
    Convolution(image, {{0,-1, 0}, {-1, 4, -1}, {0, -1, 0}});
    Pixel tmp;
    for (size_t y = 0; y < image.height; ++y) {
        for (size_t x = 0; x < image.width; ++x) {
            if (image.GetColor(x, y).red > tmp_threshold) {
                tmp = {1, 1, 1};
            } else {
                tmp = {0, 0, 0};
            }
            image.SetColor(tmp, x, y);
        }
    }
    std::cout << "EdgeDetection was applied\n";
}

PersonalFilter::PersonalFilter(Image extra_image, int width, int height, size_t x_0, size_t y_0) : extra_image(extra_image), width(width), height(height), x_0(x_0), y_0(y_0) {
}

void PersonalFilter::Apply(Image& image) {
    extra_image.width = fmin(extra_image.width, width);
    extra_image.height = fmin(extra_image.height, height);

    size_t i = 0;
    size_t j = 0;
    for (size_t y = y_0; y < fmin(image.height, extra_image.height + y_0) ; ++y) {
        for (size_t x = x_0; x < fmin(image.width, extra_image.width + x_0); ++x) {
            image.SetColor(extra_image.pixels[i][j], x, y);
            ++i;
        }
        ++j;
        i = 0;
    }
    std::cout << "PersonalFilter was applied\n";
}
