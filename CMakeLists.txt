cmake_minimum_required(VERSION 3.10)
project(vizkit3d_debug_drawings VERSION 0.1)

option(WITH_PORTS "Build with rock port support" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
#add_subdirectory(test)