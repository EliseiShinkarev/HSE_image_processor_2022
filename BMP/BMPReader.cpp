#include "BMP.h"

#include <iostream>

void BMP::Read(std::string filename) {
    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cout << "File can not be opened (BMPReader)" << '\n';
        return;
    }

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));

    if (file_header.file_type != 0x4d42) {
        std::cout << "This file is not .bmp format" << '\n';
        file.close();
        return;
    }

    file.read(reinterpret_cast<char*>(&information_header), sizeof(information_header));
    im.width = information_header.width;
    im.height = information_header.height;
    im.pixels = std::vector<std::vector<Pixel>>(information_header.width, std::vector<Pixel>(information_header.height));
    const int padding_amount = ((4 - (information_header.width * 3) % 4) % 4);

    for (size_t y = 0; y < information_header.height; ++y) {
        for (size_t x = 0; x < information_header.width; ++x) {
            unsigned char color[3];
            file.read(reinterpret_cast<char*>(color), 3);

            im.pixels[x][y].red = color[2] / 255.0;
            im.pixels[x][y].green = color[1] / 255.0;
            im.pixels[x][y].blue = color[0] / 255.0;
        }
        file.ignore(padding_amount);
    }
    file.close();
    std::cout << "file was read\n";
}