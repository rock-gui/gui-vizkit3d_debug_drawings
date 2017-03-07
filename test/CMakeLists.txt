add_definitions(-DENABLE_DEBUG_DRAWINGS)
rock_executable(draw_test draw_test.cpp
    DEPS 
        vizkit3d_debug_drawings
    DEPS_PKGCONFIG 
        base-types 
)

find_package(Boost COMPONENTS serialization iostreams)

rock_testsuite(serialization_test 
    suite.cpp
    serialization_test.cpp
    DEPS vizkit3d_debug_drawings
    DEPS_PLAIN
        Boost_SERIALIZATION
        Boost_IOSTREAMS
)