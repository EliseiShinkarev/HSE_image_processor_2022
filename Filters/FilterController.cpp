#include "BMP.h"
#include "Filters.h"

#include <iostream>

void BMP::Process(filter_information pi, Image& image, Image& extra_image) {
    std::vector<Filter*> filters;
    for (const auto& filter : pi) {
        if (filter.first == "-neg") {
            filters.push_back(new Negative());
        } else if (filter.first == "-gs") {
            filters.push_back(new Grayscale());
        } else if (filter.first == "-sharp") {
            filters.push_back(new Sharpening());
        } else if (filter.first == "-edge") {
            filters.push_back(new Grayscale());
            filters.push_back(new EdgeDetection(static_cast<int>(filter.second[0])));
        } else if (filter.first == "-pf") {
            filters.push_back(new PersonalFilter(extra_image, static_cast<int>(filter.second[0]), static_cast<int>(filter.second[1]), filter.second[2], filter.second[3]));
        } else {
            std::cout << "Wrong filter" << '\n';
        }
    }
    for (Filter* filter : filters) {
        filter->Apply(image);
    }
}
