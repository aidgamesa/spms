cmake_minimum_required(VERSION 3.0)
project(spms-deps)
add_subdirectory(argparse)
include_directories(argparse)
add_subdirectory(inih)
include_directories(inih)

set(ARGPARSE_SHARED OFF)
set(BUILD_SHARED_LIBS OFF)