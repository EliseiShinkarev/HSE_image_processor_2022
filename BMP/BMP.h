#pragma once

#include "Image.h"
#include "Getopt.h"

#include <fstream>
#include <string>

#pragma pack(push, 1)

struct BMPHeader {
    uint16_t file_type{0};
    uint32_t file_size{0};
    uint16_t reserved_1{0};
    uint16_t reserved_2{0};
    uint32_t offset{0};
};

struct DIBHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};

    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t size_image{0};

    int32_t x_pixels_pm{0};
    int32_t y_pixels_pm{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

#pragma pack(pop)

class BMP {
public:
    Image im;
    static BMPHeader file_header;
    static DIBHeader information_header;
    void Read(std::string filename);
    void Write(std::string path) const;
    static void Process(filter_information pi, Image& image, Image& extra_image);
};
