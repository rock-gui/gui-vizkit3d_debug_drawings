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
    drawingManager->addPlot(getDrawingName(), x, y);
}

PlotCommand::PlotCommand(const std::string& drawingName, double x, double y):
        Command(drawingName), x(x), y(y)
{}

PlotCommand::PlotCommand() : Command("default"), x(0), y(0)
{}



PlotCommand::~PlotCommand()
{}



    
}