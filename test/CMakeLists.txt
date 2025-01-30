

if (ROCK_QT_VERSION_4)
    rock_executable(draw_test_standalone draw_test_standalone.cpp
        DEPS
            vizkit3d_debug_drawings
        NOINSTALL
    )
    target_compile_definitions(draw_test_standalone PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_standalone PRIVATE cxx_std_11)




    find_package(Boost COMPONENTS serialization iostreams)
    rock_executable(draw_test_attach draw_test_attach.cpp
        DEPS
            vizkit3d_debug_drawings
        NOINSTALL
    )
    target_compile_definitions(draw_test_attach PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_attach PRIVATE cxx_std_11)



    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
    rock_testsuite(serialization_test
        suite.cpp
        serialization_test.cpp
        DEPS vizkit3d_debug_drawings
        DEPS_PLAIN
            Boost_SERIALIZATION
            Boost_IOSTREAMS
        NOINSTALL
    )
    target_compile_definitions(serialization_test PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_link_libraries(serialization_test ${Boost_LIBRARIES} )
    target_compile_features(serialization_test PRIVATE cxx_std_11)


    #draw_test_disabled does not set -DENABLE_DEBUG_DRAWINGS to test if everything is disabled correctly
    rock_executable(draw_test_disabled draw_test_disable.cpp
        DEPS
            vizkit3d_debug_drawings
        NOINSTALL
    )
    target_compile_features(draw_test_disabled PRIVATE cxx_std_11)
endif()



if (ROCK_QT_VERSION_5)
    rock_executable(draw_test_standalone-qt5 draw_test_standalone.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
        NOINSTALL
    )
    target_compile_definitions(draw_test_standalone-qt5 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_standalone-qt5 PRIVATE cxx_std_11)




    find_package(Boost COMPONENTS serialization iostreams)
    rock_executable(draw_test_attach-qt5 draw_test_attach.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
        NOINSTALL
    )
    target_compile_definitions(draw_test_attach-qt5 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_attach-qt5 PRIVATE cxx_std_11)



    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
    rock_testsuite(serialization_test-qt5
        suite.cpp
        serialization_test.cpp
        DEPS vizkit3d_debug_drawings-qt5
        DEPS_PLAIN
            Boost_SERIALIZATION
            Boost_IOSTREAMS
        NOINSTALL
    )
    target_compile_definitions(serialization_test-qt5 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_link_libraries(serialization_test-qt5 ${Boost_LIBRARIES} )
    target_compile_features(serialization_test-qt5 PRIVATE cxx_std_11)


    #draw_test_disabled does not set -DENABLE_DEBUG_DRAWINGS to test if everything is disabled correctly
    rock_executable(draw_test_disabled-qt5 draw_test_disable.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
        NOINSTALL
    )
    target_compile_features(draw_test_disabled-qt5 PRIVATE cxx_std_11)
endif()

rock_library(draw_test_library_enabled draw_test_library.cpp
    DEPS
        vizkit3d_debug_drawings-commands
    NOINSTALL
    )
target_compile_definitions(draw_test_library_enabled PRIVATE -DENABLE_DEBUG_DRAWINGS)
target_compile_features(draw_test_library_enabled PRIVATE cxx_std_11)

rock_library(draw_test_library_disabled draw_test_library.cpp
    DEPS
        vizkit3d_debug_drawings-commands
    NOINSTALL
    )
target_compile_features(draw_test_library_disabled PRIVATE cxx_std_11)

if (ROCK_QT_VERSION_4)
    rock_executable(draw_test_lib_enabled_app_enabled draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings
            draw_test_library_enabled
        NOINSTALL
    )
    target_compile_definitions(draw_test_lib_enabled_app_enabled PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_enabled_app_enabled PRIVATE cxx_std_11)

    rock_executable(draw_test_lib_disabled_app_enabled draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings
            draw_test_library_disabled
        NOINSTALL
    )
    target_compile_definitions(draw_test_lib_disabled_app_enabled PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_disabled_app_enabled PRIVATE cxx_std_11)

    rock_executable(draw_test_lib_disabled_app_disabled draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings
            draw_test_library_disabled
        NOINSTALL
    )
    target_compile_features(draw_test_lib_disabled_app_disabled PRIVATE cxx_std_11)

    rock_executable(draw_test_lib_enabled_app_disabled draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings
            draw_test_library_enabled
        NOINSTALL
    )
    target_compile_features(draw_test_lib_enabled_app_disabled PRIVATE cxx_std_11)
endif()

if (ROCK_QT_VERSION_5)
    rock_executable(draw_test_lib_enabled_app_enabled-qt5 draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
            draw_test_library_enabled
        NOINSTALL
    )
    target_compile_definitions(draw_test_lib_enabled_app_enabled-qt5 PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_enabled_app_enabled-qt5 PRIVATE cxx_std_11)

    rock_executable(draw_test_lib_disabled_app_enabled-qt5 draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
            draw_test_library_disabled
        NOINSTALL
    )
    target_compile_definitions(draw_test_lib_disabled_app_enabled-qt5 PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_disabled_app_enabled-qt5 PRIVATE cxx_std_11)

    rock_executable(draw_test_lib_disabled_app_disabled-qt5 draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
            draw_test_library_disabled
        NOINSTALL
    )
    target_compile_features(draw_test_lib_disabled_app_disabled-qt5 PRIVATE cxx_std_11)

    rock_executable(draw_test_lib_enabled_app_disabled-qt5 draw_test_lib_app.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
            draw_test_library_enabled
        NOINSTALL
    )
    target_compile_features(draw_test_lib_enabled_app_disabled-qt5 PRIVATE cxx_std_11)
endif()

if(WITH_PORTS)
add_subdirectory(ports)
endif(WITH_PORTS)
