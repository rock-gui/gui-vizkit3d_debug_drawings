
find_package(PkgConfig REQUIRED) 

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Boost REQUIRED COMPONENTS serialization system)

set(DEPSPLAIN Boost_SERIALIZATION BOOST_SYSTEM)

pkg_check_modules(VIZKIT3D REQUIRED IMPORTED_TARGET vizkit3d)
pkg_check_modules(OSGVIZ REQUIRED IMPORTED_TARGET osgViz)
pkg_check_modules(PRIM_FACTORY REQUIRED IMPORTED_TARGET PrimitivesFactory)


set(SOURCE_FILES
        DrawingManager.cpp
        DeclaredChannels.cpp
        DebugDrawing.cpp
        DebugDrawingColors.cpp
        commands/DrawCommand.cpp
        commands/Command.cpp
        commands/RemoveDrawingCommand.cpp
        commands/ClearDrawingCommand.cpp
        commands/CommandBuffer.cpp
        commands/PlotCommand.cpp
        commands/ClearPlotCommand.cpp
        commands/primitives/DrawSphereCommand.cpp
        commands/primitives/DrawTextCommand.cpp
        commands/primitives/DrawRingCommand.cpp
        commands/primitives/DrawWireframeBoxCommand.cpp
        commands/primitives/DrawArrowCommand.cpp
        commands/primitives/DrawPolyLineCommand.cpp
        commands/primitives/DrawCylinderCommand.cpp
        commands/primitives/DrawAxesCommand.cpp
        commands/primitives/DrawAABBCommand.cpp
        dispatch/CommandDispatcherFactory.cpp
        dispatch/StandaloneDispatcher.cpp
        dispatch/ExistingWidgetDispatcher.cpp
)

set(HEADER_FILES
        DebugDrawing.hpp
        Drawing.hpp
        DrawingManager.hpp
        DeclaredChannels.hpp
        DebugDrawingColors.hpp
        StaticDeclarationHelpers.hpp
        PlotDataPoint.hpp
        commands/DrawCommand.hpp
        commands/Command.hpp
        commands/RemoveDrawingCommand.hpp
        commands/ClearDrawingCommand.hpp
        commands/CommandBuffer.hpp
        commands/PlotCommand.hpp
        commands/ClearPlotCommand.hpp
        commands/primitives/DrawSphereCommand.hpp
        commands/primitives/DrawTextCommand.hpp
        commands/primitives/DrawRingCommand.hpp
        commands/primitives/DrawWireframeBoxCommand.hpp
        commands/primitives/DrawArrowCommand.hpp
        commands/primitives/DrawPolyLineCommand.hpp
        commands/primitives/DrawPolyLineCommand.hpp
        commands/primitives/DrawAxesCommand.hpp
        commands/primitives/DrawAABBCommand.hpp
        commands/BoostSerializationExports.hpp
        dispatch/ICommandDispatcher.hpp
        dispatch/CommandDispatcherFactory.hpp
        dispatch/StandaloneDispatcher.hpp
        dispatch/ExistingWidgetDispatcher.hpp
)

# includes should be relative to the src folder
include_directories(.)

# TODO make this work again
# if(WITH_PORTS)

#   message("Building with port support")
  
#   set(OROCOS_TARGET "$ENV{OROCOS_TARGET}") #is needed when using orocos-rtt
  
#   set(SOURCE_FILES ${SOURCE_FILES} dispatch/PortDispatcher.cpp)
#   set(HEADER_FILES ${HEADER_FILES} dispatch/PortDispatcher.hpp)
#   set(DEPS ${DEPS} orocos-rtt-${OROCOS_TARGET})
   
#   add_definitions(-DUSE_PORTS)
#   set(vizkit3d_debug_drawings_PKGCONFIG_CFLAGS -DUSE_PORTS)
  
# else()

#   message("Building without port support")
  
# endif(WITH_PORTS)


add_library(vizkit3d_debug_drawings SHARED ${SOURCE_FILES})

target_link_libraries(vizkit3d_debug_drawings 
                      ${Boost_LIBRARIES}
                      PkgConfig::VIZKIT3D
                      PkgConfig::OSGVIZ
                      PkgConfig::PRIM_FACTORY)


configure_file(vizkit3d_debug_drawings.pc.in vizkit3d_debug_drawings.pc @ONLY)

include(GNUInstallDirs)

install(TARGETS vizkit3d_debug_drawings
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

#install headers
install(DIRECTORY .
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vizkit3d_debug_drawings
        FILES_MATCHING PATTERN "*.hpp")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vizkit3d_debug_drawings.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# TODO add pc.in configuration and installation stuff


