rock_vizkit_plugin(vizkit3d_debug_drawings-viz
    DrawingVisualization.cpp
    DEPS
        vizkit3d_debug_drawings
    MOC
        DrawingVisualization.hpp
    HEADERS
        DrawingVisualization.hpp
)

rock_vizkit_plugin(vizkit3d_debug_drawings_plot-viz
    DebugPlotVisualization.cpp
    DEPS
        vizkit3d_debug_drawings
    DEPS_PKGCONFIG
        rock_widget_collection
    MOC
        DebugPlotVisualization.hpp
    HEADERS
        DebugPlotVisualization.hpp
)
  
        
        
rock_vizkit_plugin(vizkit3d_debug_drawings_command-viz
    DebugDrawingVisualization.cpp
    DEPS
        vizkit3d_debug_drawings
        vizkit3d_debug_drawings-viz
    MOC
        DebugDrawingVisualization.hpp
    HEADERS
        DebugDrawingVisualization.hpp
)
         