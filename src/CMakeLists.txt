set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(WITH_PORTS "Build with rock port support" ON)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})


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

set(DEPS 
        vizkit3d
        osgViz
        PrimitivesFactory
)

find_package(Boost REQUIRED COMPONENTS serialization system)
set(DEPSPLAIN Boost_SERIALIZATION BOOST_SYSTEM)


if(WITH_PORTS)

  message("Building with port support")
  
  set(OROCOS_TARGET "$ENV{OROCOS_TARGET}") #is needed when using orocos-rtt
  
  set(SOURCE_FILES ${SOURCE_FILES} dispatch/PortDispatcher.cpp)
  set(HEADER_FILES ${HEADER_FILES} dispatch/PortDispatcher.hpp)
  set(DEPS ${DEPS} orocos-rtt-${OROCOS_TARGET})
   
  add_definitions(-DUSE_PORTS)
  set(vizkit3d_debug_drawings_PKGCONFIG_CFLAGS -DUSE_PORTS)
  
else()

  message("Building without port support")
  
endif(WITH_PORTS)



rock_library(vizkit3d_debug_drawings
    SOURCES ${SOURCE_FILES}
    HEADERS ${HEADER_FILES}
    DEPS_PKGCONFIG ${DEPS}
    DEPS_PLAIN ${DEPSPLAIN}
)

target_link_libraries(vizkit3d_debug_drawings ${Boost_LIBRARIES})


