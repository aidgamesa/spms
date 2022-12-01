cmake_minimum_required(VERSION 3.0)
project(spms)

file(GLOB SRC src/*.c)

include_directories(include)

add_subdirectory(deps)

add_executable(spms ${SRC})
target_link_libraries(spms archive argparse)