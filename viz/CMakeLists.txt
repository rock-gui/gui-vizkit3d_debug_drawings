
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

if (ROCK_QT_VERSION_4)
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
        qcustomplot.cc
        DEPS
            vizkit3d_debug_drawings
        MOC
            DebugPlotVisualization.hpp
            qcustomplot.h
        HEADERS
            DebugPlotVisualization.hpp
            qcustomplot.h
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
endif()

if (ROCK_QT_VERSION_5)
    rock_vizkit_plugin_qt5(vizkit3d_debug_drawings-viz-qt5
        DrawingVisualization.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
        MOC5
            DrawingVisualization.hpp
        HEADERS
            DrawingVisualization.hpp
    )

    rock_vizkit_plugin_qt5(vizkit3d_debug_drawings_plot-viz-qt5
        DebugPlotVisualization.cpp
        qcustomplot.cc
        DEPS
            vizkit3d_debug_drawings-qt5
        MOC5
            DebugPlotVisualization.hpp
            qcustomplot.h
        HEADERS
            DebugPlotVisualization.hpp
            qcustomplot.h
    )



    rock_vizkit_plugin_qt5(vizkit3d_debug_drawings_command-viz-qt5
        DebugDrawingVisualization.cpp
        DEPS
            vizkit3d_debug_drawings-qt5
            vizkit3d_debug_drawings-viz-qt5
        MOC5
            DebugDrawingVisualization.hpp
        HEADERS
            DebugDrawingVisualization.hpp
    )
endif()
