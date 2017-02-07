rock_library(vizkit3dDebugDrawings
    SOURCES
        DrawingManager.cpp
        DrawingCommands/SphereCommand.cpp
    HEADERS 
        DebugDrawCommand.h
        DrawingCommands/SphereCommand.h
        DebugDrawing.h
        Drawing.h
        DrawingManager.h
    DEPS_PKGCONFIG vizkit3d osgViz )

