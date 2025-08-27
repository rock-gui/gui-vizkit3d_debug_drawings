
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

rock_qt_vizkit_plugin(
    TARGETPREFIX vizkit3d_debug_drawings-viz
    QT4_SUFFIX ""
    MISSINGQTDEPS_NOBUILD
    SOURCES
        DrawingVisualization.cpp
    DEPS_QT
        vizkit3d_debug_drawings
    MOC
        DrawingVisualization.hpp
    HEADERS
        DrawingVisualization.hpp
)

rock_qt_vizkit_plugin(
    TARGETPREFIX vizkit3d_debug_drawings_plot-viz
    QT4_SUFFIX ""
    MISSINGQTDEPS_NOBUILD
    SOURCES
        DebugPlotVisualization.cpp
        qcustomplot.cc
    DEPS_QT
        vizkit3d_debug_drawings
    MOC
        DebugPlotVisualization.hpp
        qcustomplot.h
    HEADERS
        DebugPlotVisualization.hpp
        qcustomplot.h
)

rock_qt_vizkit_plugin(
    TARGETPREFIX vizkit3d_debug_drawings_command-viz
    QT4_SUFFIX ""
    MISSINGQTDEPS_NOBUILD
    SOURCES
        DebugDrawingVisualization.cpp
    DEPS_QT
        vizkit3d_debug_drawings
        vizkit3d_debug_drawings-viz
    MOC
        DebugDrawingVisualization.hpp
    HEADERS
        DebugDrawingVisualization.hpp
)
