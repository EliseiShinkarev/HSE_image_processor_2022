#include "BMP.h"

#include <iostream>

int main(int argc, char** argv) {

    if (argc <= 2) {
        std::cout << "Описание формата аргументов командной строки:\n"

                     "{имя программы} {путь к входному файлу} {путь к выходному файлу} [-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...] [-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...";

        return 0;
    }

    const ParsedInput parsed_input = ParseCommandLine(argc, argv);
    BMP bmp;
    bmp.Read(parsed_input.input_file);

    BMP bmp_extra;
    if (!parsed_input.extra_file.empty()) {
        bmp_extra.Read(parsed_input.extra_file);
    } else {
        bmp_extra.im = bmp.im;
    }

    bmp.Process(parsed_input.filter_data, bmp.im, bmp_extra.im);
    if (!parsed_input.output_file.empty()) {
        bmp.Write(parsed_input.output_file);
    }

    return 0;
}
