rock_vizkit_plugin(vizkit3dDebugDrawings-viz
    DrawingVisualization.cpp
    DEPS
        vizkit3d_debug_drawings
    MOC
        DrawingVisualization.hpp
    HEADERS
        DrawingVisualization.hpp
)
        
        
rock_vizkit_plugin(vizkit3dDebugCommand-viz
    DebugDrawingVisualization.cpp
    DEPS
        vizkit3d_debug_drawings
        vizkit3dDebugDrawings-viz
    MOC
        DebugDrawingVisualization.hpp
    HEADERS
        DebugDrawingVisualization.hpp
)
         