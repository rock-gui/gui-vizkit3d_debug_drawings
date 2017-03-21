rock_vizkit_plugin(vizkit3dDebugDrawings-viz
    DrawingVisualization.cpp
    DEPS
        vizkit3d_debug_drawings
    MOC
        DrawingVisualization.hpp
    HEADERS
        DrawingVisualization.hpp
)

rock_vizkit_plugin(vizkit3dDebugDrawingsPlot-viz
    DebugPlotVisualization.cpp
    qcustomplot/qcustomplot.cpp
    DEPS
        vizkit3d_debug_drawings
    MOC
        DebugPlotVisualization.hpp
        qcustomplot/qcustomplot.h
    HEADERS
        DebugPlotVisualization.hpp
        qcustomplot/qcustomplot.h
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
         