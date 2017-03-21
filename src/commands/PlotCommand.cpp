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

PlotCommand::PlotCommand(const std::string& drawingName, const base::Vector2d& dataPoint):
        Command(drawingName), dataPoint(dataPoint)
{}

PlotCommand::PlotCommand() : Command("default"), dataPoint(base::Vector2d::Zero())
{}



PlotCommand::~PlotCommand()
{}



    
}