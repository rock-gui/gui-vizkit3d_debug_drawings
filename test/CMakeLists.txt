add_definitions(-DENABLE_DEBUG_DRAWINGS)
rock_executable(draw_test draw_test.cpp
    DEPS 
        vizkit3d_debug_drawings
)

find_package(Boost COMPONENTS serialization iostreams)


find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

rock_testsuite(serialization_test 
    suite.cpp
    serialization_test.cpp
    DEPS vizkit3d_debug_drawings
    DEPS_PLAIN
        Boost_SERIALIZATION
        Boost_IOSTREAMS
)