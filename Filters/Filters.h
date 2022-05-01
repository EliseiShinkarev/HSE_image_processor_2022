#include "Image.h"

#include <iostream>

class Filter {
public:
    virtual void Apply(Image& image);
    std::vector<std::vector<Pixel>> GetImageMatrix(size_t x, size_t y, Image& copy_image);
    void Convolution(Image& image, std::vector<std::vector<float>> matrix);
};

class Grayscale : public Filter {
public:
    void Apply(Image& image) override;
};

class Negative : public Filter {
public:
    void Apply(Image& image) override;
};

class Sharpening : public Filter {
public:
    void Apply(Image& image) override;
};

class EdgeDetection : public Filter {
public:
    float tmp_threshold;
    explicit EdgeDetection(int threshold);
    void Apply(Image& image) override;
};

class PersonalFilter : public Filter {
public:
    Image extra_image;
    int width;
    int height;
    size_t x_0;
    size_t y_0;
    PersonalFilter(Image extra_image, int width, int height, size_t x_0, size_t y_0);
    void Apply(Image& image) override;
};