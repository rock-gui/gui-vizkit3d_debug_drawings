option(WITH_PORTS "Build with rock port support" ON)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization system)

set(COMMANDS_SOURCE_FILES
        DebugDrawingWeakNoops.cpp
        DebugDrawingColors.cpp
        StaticDeclarationHelpersWeakNoops.cpp
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
        DebugDrawing.hpp
        DebugDrawingColors.hpp
        StaticDeclarationHelpers.hpp
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
        StaticDeclarationHelpers.cpp
        dispatch/CommandDispatcherFactory.cpp
        dispatch/StandaloneDispatcher.cpp
        dispatch/ExistingWidgetDispatcher.cpp
)

set(HEADER_FILES
        Drawing.hpp
        DrawingManager.hpp
        DeclaredChannels.hpp
        PlotDataPoint.hpp
        dispatch/ICommandDispatcher.hpp
        dispatch/CommandDispatcherFactory.hpp
        dispatch/StandaloneDispatcher.hpp
        dispatch/ExistingWidgetDispatcher.hpp
)

set(DEPS 
        vizkit3d
        osgViz
)


if(WITH_PORTS)

  message("Building with port support")
  
  set(OROCOS_TARGET "$ENV{OROCOS_TARGET}") #is needed when using orocos-rtt
  
  set(SOURCE_FILES ${SOURCE_FILES} dispatch/PortDispatcher.cpp)
  set(HEADER_FILES ${HEADER_FILES} dispatch/PortDispatcher.hpp)
  set(DEPS ${DEPS} orocos-rtt-${OROCOS_TARGET})
   
  add_definitions(-DUSE_PORTS)
  set(vizkit3d_debug_drawings-commands_PKGCONFIG_CFLAGS -DUSE_PORTS)
  set(vizkit3d_debug_drawings_PKGCONFIG_CFLAGS -DUSE_PORTS)
  set(vizkit3d_debug_drawings-ports_PKGCONFIG_CFLAGS -DUSE_PORTS)

else()

  message("Building without port support")
  
endif(WITH_PORTS)

rock_library(vizkit3d_debug_drawings-commands
    SOURCES ${COMMANDS_SOURCE_FILES}
    HEADERS ${COMMANDS_HEADER_FILES}
    DEPS_PKGCONFIG PrimitivesFactory
    LIBS Boost::serialization Boost::system Eigen3::Eigen
    )
if(WITH_PORTS)
    target_compile_definitions(vizkit3d_debug_drawings-commands PUBLIC USE_PORTS)
endif()
target_compile_features(vizkit3d_debug_drawings-commands PRIVATE cxx_std_11)

rock_library(vizkit3d_debug_drawings
    SOURCES ${SOURCE_FILES}
    HEADERS ${HEADER_FILES}
    DEPS_PKGCONFIG ${DEPS}
    DEPS vizkit3d_debug_drawings-commands Boost::serialization Boost::system
)
target_compile_features(vizkit3d_debug_drawings PRIVATE cxx_std_11)

if(WITH_PORTS)
    # vizkit3d_debug_drawings without standalone and widget dispatchers,
    # leaving just ports. It does not clash with the plain library and
    # can be linked into the same executable.
    rock_library(vizkit3d_debug_drawings-ports
        SOURCES
        DebugDrawing.cpp
        DeclaredChannels.cpp
        dispatch/CommandDispatcherFactory.cpp
        dispatch/PortDispatcher.cpp

        HEADERS
        DebugDrawing.hpp
        DeclaredChannels.hpp
        dispatch/CommandDispatcherFactory.hpp
        dispatch/ICommandDispatcher.hpp
        dispatch/PortDispatcher.hpp

        DEPS vizkit3d_debug_drawings-commands Boost::serialization Boost::system
    )

    target_compile_definitions(vizkit3d_debug_drawings-ports PRIVATE DISABLE_QT_BUILD)
    target_compile_features(vizkit3d_debug_drawings-ports PRIVATE cxx_std_11)
endif()
