# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.5)
project(vizkit3d_debug_drawings VERSION 0.1 DESCRIPTION "A ROCK library that provides methods to create 3d drawings and plot data from inside any code for debugging purpose.")
find_package(Rock)
set(ROCK_TEST_ENABLED ON)
rock_init()
rock_feature(NOCURDIR)
rock_find_qt5(OPTIONAL PrintSupport)
rock_find_qt4(OPTIONAL)

option(WITH_PORTS "Build with rock port support" ON)

rock_standard_layout()

