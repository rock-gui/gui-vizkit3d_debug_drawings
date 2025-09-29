


rock_qt_executable(
    TARGETPREFIX draw_test_standalone
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_standalone.cpp
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    DEPS_QT4
        vizkit3d_debug_drawings
    NOINSTALL
)
if(TARGET draw_test_standalone-qt4)
    target_compile_definitions(draw_test_standalone-qt4 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_standalone-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_standalone-qt5)
    target_compile_definitions(draw_test_standalone-qt5 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_standalone-qt5 PRIVATE cxx_std_11)
endif()



find_package(Boost COMPONENTS serialization iostreams)
rock_qt_executable(
    TARGETPREFIX draw_test_attach
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_attach.cpp
    DEPS_QT4
        vizkit3d_debug_drawings
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    NOINSTALL
)
if(TARGET draw_test_attach-qt4)
    target_compile_definitions(draw_test_attach-qt4 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_attach-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_attach-qt5)
    target_compile_definitions(draw_test_attach-qt5 PUBLIC -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_attach-qt5 PRIVATE cxx_std_11)
endif()

if(TARGET vizkit3d_debug_drawings)
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
endif()

if(TARGET vizkit3d_debug_drawings-qt5)
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
endif()

#draw_test_disabled does not set -DENABLE_DEBUG_DRAWINGS to test if everything is disabled correctly
rock_qt_executable(
    TARGETPREFIX draw_test_disabled
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_disable.cpp
    DEPS_QT4
        vizkit3d_debug_drawings
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    NOINSTALL
)
if(TARGET draw_test_disabled-qt4)
    target_compile_features(draw_test_disabled-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_disabled-qt5)
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

rock_qt_executable(
    TARGETPREFIX draw_test_lib_enabled_app_enabled
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_lib_app.cpp
    DEPS_QT4
        vizkit3d_debug_drawings
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    DEPS
        draw_test_library_enabled
    NOINSTALL
)
if(TARGET draw_test_lib_enabled_app_enabled-qt4)
    target_compile_definitions(draw_test_lib_enabled_app_enabled-qt4 PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_enabled_app_enabled-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_lib_enabled_app_enabled-qt5)
    target_compile_definitions(draw_test_lib_enabled_app_enabled-qt5 PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_enabled_app_enabled-qt5 PRIVATE cxx_std_11)
endif()

rock_qt_executable(
    TARGETPREFIX draw_test_lib_disabled_app_enabled
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_lib_app.cpp
    DEPS_QT4
        vizkit3d_debug_drawings
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    DEPS
        draw_test_library_disabled
    NOINSTALL
)
if(TARGET draw_test_lib_disabled_app_enabled-qt4)
    target_compile_definitions(draw_test_lib_disabled_app_enabled-qt4 PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_disabled_app_enabled-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_lib_disabled_app_enabled-qt5)
    target_compile_definitions(draw_test_lib_disabled_app_enabled-qt5 PRIVATE -DENABLE_DEBUG_DRAWINGS)
    target_compile_features(draw_test_lib_disabled_app_enabled-qt5 PRIVATE cxx_std_11)
endif()

rock_qt_executable(
    TARGETPREFIX draw_test_lib_disabled_app_disabled
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_lib_app.cpp
    DEPS_QT4
        vizkit3d_debug_drawings
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    DEPS
        draw_test_library_disabled
    NOINSTALL
)
if(TARGET draw_test_lib_disabled_app_disabled-qt4)
    target_compile_features(draw_test_lib_disabled_app_disabled-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_lib_disabled_app_disabled-qt5)
    target_compile_features(draw_test_lib_disabled_app_disabled-qt5 PRIVATE cxx_std_11)
endif()

rock_qt_executable(
    TARGETPREFIX draw_test_lib_enabled_app_disabled
    MISSINGQTDEPS_NOBUILD
    SOURCES
        draw_test_lib_app.cpp
    DEPS_QT4
        vizkit3d_debug_drawings
    DEPS_QT5
        vizkit3d_debug_drawings-qt5
    DEPS
        draw_test_library_enabled
    NOINSTALL
)
if(TARGET draw_test_lib_enabled_app_disabled-qt4)
    target_compile_features(draw_test_lib_enabled_app_disabled-qt4 PRIVATE cxx_std_11)
endif()
if(TARGET draw_test_lib_enabled_app_disabled-qt5)
    target_compile_features(draw_test_lib_enabled_app_disabled-qt5 PRIVATE cxx_std_11)
endif()

if(WITH_PORTS)
add_subdirectory(ports)
endif(WITH_PORTS)
