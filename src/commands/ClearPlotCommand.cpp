#include "ClearPlotCommand.hpp"
#include "DrawingManager.hpp"

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
