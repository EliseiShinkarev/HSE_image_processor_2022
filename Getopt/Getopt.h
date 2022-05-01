#include <map>
#include <string>
#include <vector>

using filter_name = std::string;
using filter_options = std::vector<float>;
using filter_information = std::vector<std::pair<filter_name, filter_options>>;

struct ParsedInput {
    std::string input_file;
    std::string output_file;
    std::string extra_file;
    filter_information filter_data;
};

ParsedInput ParseCommandLine(int argc, char** argv);
