rock_library(vizkit3dDebugDrawings
    SOURCES
        DrawingManager.cpp
        DebugDrawing.cpp
        DebugDrawingColors.cpp
        CommandDispatcher.cpp
        commands/DrawCommand.cpp
        commands/primitives/DrawSphereCommand.cpp
    HEADERS 
        DebugDrawing.h
        Drawing.h
        DrawingManager.h
        DebugDrawingColors.h
        CommandDispatcher.h
        commands/DrawCommand.h
        commands/Command.h
        commands/primitives/DrawSphereCommand.h
    DEPS_PKGCONFIG vizkit3d osgViz base-types)

