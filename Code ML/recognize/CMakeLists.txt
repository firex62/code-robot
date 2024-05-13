cmake_minimum_required(VERSION 2.8)

project(recognize)

find_package(jetson-utils)
find_package(jetson-inference)

find_package(CUDA)

link_directories(/usr/lib/aarch64-linux-gnu/tegra)

cuda_add_executable(recognize classify.cpp)

target_link_libraries(recognize jetson-inference)