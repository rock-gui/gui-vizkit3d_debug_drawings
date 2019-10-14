


rock_executable(draw_test_standalone draw_test_standalone.cpp
    DEPS 
        vizkit3d_debug_drawings
)
target_compile_definitions(draw_test_standalone PUBLIC -DENABLE_DEBUG_DRAWINGS)




find_package(Boost COMPONENTS serialization iostreams)
rock_executable(draw_test_attach draw_test_attach.cpp
    DEPS 
        vizkit3d_debug_drawings
)
target_compile_definitions(draw_test_attach PUBLIC -DENABLE_DEBUG_DRAWINGS)



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
target_compile_definitions(serialization_test PUBLIC -DENABLE_DEBUG_DRAWINGS)
target_link_libraries(serialization_test ${Boost_LIBRARIES} )


#draw_test_disabled does not set -DENABLE_DEBUG_DRAWINGS to test if everything is disabled correctly
rock_executable(draw_test_disabled draw_test_disable.cpp
    DEPS 
        vizkit3d_debug_drawings
)
