#pragma once

#include <fstream>
#include <string>
#include <vector>

struct Pixel {
    float red;
    float green;
    float blue;

    Pixel();
    Pixel(float red, float green, float blue);
    Pixel& operator=(Pixel const& pixel);
    Pixel& operator+=(Pixel const& pixel);
    Pixel& operator*=(Pixel const& pixel);
    Pixel& operator*=(float value);
    bool operator==(Pixel const& pixel);
    bool operator!=(Pixel const& pixel);
};

class Image {
public:
    Image();
    Image(int width, int height);
    Pixel GetColor(int x, int y) const;
    void SetColor(const Pixel& pixel, int x, int y);

    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;

    Image& Copy(const Image& im);
    Image& operator=(const Image& im);
    bool operator==(const Image& im);
    static bool ImageExists(const Image& im, int x, int y);

};
