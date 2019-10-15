#include "ClearPlotCommand.hpp"
#include <vizkit3d_debug_drawings/DrawingManager.hpp>

namespace vizkit3dDebugDrawings
{
    
ClearPlotCommand* ClearPlotCommand::clone() const
{
    return new ClearPlotCommand(*this);
}

void ClearPlotCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->clearPlot(getDrawingChannel());
}

ClearPlotCommand::ClearPlotCommand(const std::string& drawingChannel) :
        Command(drawingChannel)
{
    
}

ClearPlotCommand::ClearPlotCommand() : Command("default")
{}

ClearPlotCommand::~ClearPlotCommand()
{}
    
}
