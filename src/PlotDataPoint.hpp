#pragma once
#include<Eigen/Core>

namespace vizkit3dDebugDrawings
{
    
    struct PlotDataPoint
    {
        std::string name; //name of the plot
        Eigen::Vector2d data;
    };
}
