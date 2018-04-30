#include "PlotCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>

namespace vizkit3dDebugDrawings
{
    
PlotCommand* PlotCommand::clone() const
{
    return new PlotCommand(*this);
}

void PlotCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->addPlotDataPoint(getDrawingName(), dataPoint);
}

PlotCommand::PlotCommand(const std::string& drawingGroupName, const Eigen::Vector2d& dataPoint):
        Command(drawingGroupName), dataPoint(dataPoint)
{}

PlotCommand::PlotCommand() : Command("default"), dataPoint(Eigen::Vector2d::Zero())
{}



PlotCommand::~PlotCommand()
{}



    
}