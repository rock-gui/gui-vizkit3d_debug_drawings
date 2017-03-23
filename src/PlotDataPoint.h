#pragma once
#include <base/Eigen.hpp>

namespace vizkit3dDebugDrawings
{
    
    struct PlotDataPoint
    {
        std::string name; //name of the plot
        base::Vector2d data;
    };
}
