cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled Filters.cpp Filters.h Image.h image_processor.cpp BMPReader.cpp BMP.cpp Getopt.cpp Getopt.h FilterController.cpp Image.cpp test_getopt.cpp test_reader_writer.cpp BMP.h test_filters.cpp)
