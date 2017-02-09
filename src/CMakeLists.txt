rock_library(vizkit3dDebugDrawings
    SOURCES
        DrawingManager.cpp
        DrawingCommands/SphereCommand.cpp
        DebugDrawing.cpp
        DebugDrawingColors.cpp
    HEADERS 
        DebugDrawCommand.h
        DrawingCommands/SphereCommand.h
        DebugDrawing.h
        Drawing.h
        DrawingManager.h
        DebugDrawingColors.h
    DEPS_PKGCONFIG vizkit3d osgViz base-types)

