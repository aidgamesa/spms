cmake_minimum_required(VERSION 3.0)
project(spms)

file(GLOB SRC src/*.cpp)

add_executable(spms ${SRC})
target_link_libraries(spms archive)