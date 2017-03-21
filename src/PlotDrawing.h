#pragma once
#include <base/Eigen.hpp>

namespace vizkit3dDebugDrawings
{
    /**A named collection of drawables */
    struct PlotDrawing
    {
        std::string name;
        base::Vector2d data;
    };
}
