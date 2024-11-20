set(OROCOS_TARGET "gnulinux")
pkg_check_modules(orocos-rtt-corba "orocos-rtt-corba-${OROCOS_TARGET}" IMPORTED_TARGET)

if(orocos-rtt-corba_FOUND)
    add_executable(deployment
        main-orogen_default_component__Task.cpp
        orogen/tasks/DeployerComponent.cpp
        tasks/Task.cpp
        orogen/tasks/TaskBase.cpp
        )
    target_include_directories(deployment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(deployment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/typekit)
    target_include_directories(deployment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/orogen/typekit/type_info)
    target_link_libraries(deployment PRIVATE
        PkgConfig::orocos-rtt-corba
        vizkit3d_debug_drawings-ports
        )
    target_compile_definitions(deployment PRIVATE ENABLE_DEBUG_DRAWINGS)
    target_compile_features(deployment PRIVATE cxx_std_11)

endif(orocos-rtt-corba_FOUND)
