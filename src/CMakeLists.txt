set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(WITH_PORTS "Build with rock port support" OFF)


set(SOURCE_FILES
        DrawingManager.cpp
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
        DebugDrawing.h
        Drawing.h
        DrawingManager.h
        DebugDrawingColors.h
        PlotDataPoint.h
        commands/DrawCommand.h
        commands/Command.h
        commands/RemoveDrawingCommand.h
        commands/ClearDrawingCommand.h
        commands/CommandBuffer.h
        commands/PlotCommand.h
        commands/ClearPlotCommand.h
        commands/primitives/DrawSphereCommand.h
        commands/primitives/DrawTextCommand.h
        commands/primitives/DrawRingCommand.h
        commands/primitives/DrawWireframeBoxCommand.h
        commands/primitives/DrawArrowCommand.h
        commands/primitives/DrawPolyLineCommand.h
        commands/primitives/DrawPolyLineCommand.h
        commands/primitives/DrawAxesCommand.h
        commands/primitives/DrawAABBCommand.h
        commands/BoostSerializationExports.h
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



if(WITH_PORTS)

  message("Building with port support")
  
  set(OROCOS_TARGET "$ENV{OROCOS_TARGET}") #is needed when using orocos-rtt
  
  set(SOURCE_FILES ${SOURCE_FILES} dispatch/PortDispatcher.cpp)
  set(HEADER_FILES ${HEADER_FILES} dispatch/PortDispatcher.hpp)
  set(DEPS ${DEPS} boost_serialization  orocos-rtt-${OROCOS_TARGET} orocos_cpp)
  add_definitions(-DUSE_PORTS)
  
else()

  message("Building without port support")
  
endif(WITH_PORTS)



rock_library(vizkit3d_debug_drawings
    SOURCES ${SOURCE_FILES}
    HEADERS ${HEADER_FILES}
    DEPS_PKGCONFIG ${DEPS}
)
