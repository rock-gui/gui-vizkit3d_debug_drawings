option(WITH_PORTS "Build with rock port support" ON)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(COMMANDS_SOURCE_FILES
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
        )

set(COMMANDS_HEADER_FILES
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
        )

set(SOURCE_FILES
        DrawingManager.cpp
        DeclaredChannels.cpp
        DebugDrawing.cpp
        DebugDrawingColors.cpp
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
        dispatch/ICommandDispatcher.hpp
        dispatch/CommandDispatcherFactory.hpp
        dispatch/StandaloneDispatcher.hpp
        dispatch/ExistingWidgetDispatcher.hpp
)

set(DEPS osgViz)

find_package(Boost REQUIRED COMPONENTS serialization system)


if(WITH_PORTS)

  message("Building with port support")
  
  set(OROCOS_TARGET "$ENV{OROCOS_TARGET}") #is needed when using orocos-rtt
  
  set(SOURCE_FILES ${SOURCE_FILES} dispatch/PortDispatcher.cpp)
  set(HEADER_FILES ${HEADER_FILES} dispatch/PortDispatcher.hpp)
  set(DEPS ${DEPS} orocos-rtt-${OROCOS_TARGET})
   
  add_definitions(-DUSE_PORTS)
  set(vizkit3d_debug_drawings-commands_PKGCONFIG_CFLAGS -DUSE_PORTS)
  set(vizkit3d_debug_drawings_PKGCONFIG_CFLAGS -DUSE_PORTS)
  set(vizkit3d_debug_drawings-qt5_PKGCONFIG_CFLAGS -DUSE_PORTS)

else()

  message("Building without port support")
  
endif(WITH_PORTS)

rock_library(vizkit3d_debug_drawings-commands
    SOURCES ${COMMANDS_SOURCE_FILES}
    HEADERS ${COMMANDS_HEADER_FILES}
    DEPS_PKGCONFIG PrimitivesFactory
    DEPS Boost::serialization Boost::system
    )

if (ROCK_QT_VERSION_4)
    rock_library(vizkit3d_debug_drawings
        SOURCES ${SOURCE_FILES}
        HEADERS ${HEADER_FILES}
        DEPS_PKGCONFIG
            ${DEPS}
            vizkit3d
        DEPS vizkit3d_debug_drawings-commands Boost::serialization Boost::system
    )
endif()

if (ROCK_QT_VERSION_5)
    rock_library(vizkit3d_debug_drawings-qt5
        SOURCES ${SOURCE_FILES}
        HEADERS ${HEADER_FILES}
        DEPS_PKGCONFIG
            ${DEPS}
            vizkit3d-qt5
        LIBS Qt5::PrintSupport 
        DEPS vizkit3d_debug_drawings-commands Boost::serialization Boost::system
    )
endif()


