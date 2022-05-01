#include "Getopt.h"

ParsedInput ParseCommandLine(int argc, char** argv) {
    ParsedInput pi;
    std::string current_filter;
    for (size_t i = 0; i < argc; ++i) {
        std::string str = argv[i];
        if (!pi.input_file.empty() && (str.back() == 'p' || str.back() == 'P') && pi.output_file.empty()) {
            pi.output_file = argv[i];
        } else if (pi.output_file.empty() && (str.back() == 'p' || str.back() == 'P')) {
            pi.input_file = argv[i];
        } else if (argv[i][0] == '-') {
            current_filter = argv[i];
            pi.filter_data.push_back(std::make_pair(current_filter, filter_options()));
        } else if (isdigit(argv[i][0])) {
            pi.filter_data.back().second.push_back(std::stof(str));
        } else if (!pi.output_file.empty() && !pi.input_file.empty() && (str.back() == 'p' || str.back() == 'P')) {
            pi.extra_file = argv[i];
        }
    }

    return pi;
}
