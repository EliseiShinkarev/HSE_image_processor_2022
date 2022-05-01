#include "BMP.h"

#include <iostream>

BMPHeader BMP::file_header;
DIBHeader BMP::information_header;

void BMP::Write(std::string path) const {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cout << "file could not be opened \n";
        return;
    }

    if (information_header.width != im.width) {
        information_header.width = im.width;
    }
    if (information_header.height != im.height) {
        information_header.height = im.height;
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding_amount = ((4 - (information_header.width * 3) % 4) % 4);
    information_header.size_image = information_header.height * information_header.width * 3;
    file_header.file_size = 14 + 40 + information_header.size_image + padding_amount * information_header.height;

    file.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));

    if (file_header.file_type != 0x4d42) {
        std::cout << "This file is not .bmp format" << '\n';
        file.close();
        return;
    }

    file.write(reinterpret_cast<char*>(&information_header), sizeof(information_header));


    for (size_t y = 0; y < information_header.height; ++y) {
        for (size_t x = 0; x < information_header.width; ++x) {
            unsigned char red = static_cast<unsigned char>(im.GetColor(x, y).red * 255);
            unsigned char green = static_cast<unsigned char>(im.GetColor(x, y).green * 255);
            unsigned char blue = static_cast<unsigned char>(im.GetColor(x, y).blue * 255);

            unsigned char color[] = {blue, green, red};
            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char*>(bmp_pad), padding_amount);
    }
    file.close();
    std::cout << "file was written\n";
}
