# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.3)
project(vizkit3d_debug_drawings VERSION 0.1 DESCRIPTION "A ROCK library that provides methods to create 3d drawings and plot data from inside any code for debugging purpose.")
find_package(Rock)
#set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(ROCK_TEST_ENABLED ON)
rock_init()
rock_find_qt5(PrintSupport)
rock_standard_layout()

