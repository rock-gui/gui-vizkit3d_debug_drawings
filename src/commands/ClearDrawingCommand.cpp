#include "ClearDrawingCommand.hpp"
#include <vizkit3d_debug_drawings/DrawingManager.hpp>


namespace vizkit3dDebugDrawings
{
ClearDrawingCommand::ClearDrawingCommand(const std::string& drawingGroupName) :
        Command(drawingGroupName)
{}

ClearDrawingCommand::ClearDrawingCommand() : Command("default")
{

}


void ClearDrawingCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->clearDrawing(getDrawingName());
}

ClearDrawingCommand::~ClearDrawingCommand()
{}

ClearDrawingCommand* ClearDrawingCommand::clone() const
{
    return new ClearDrawingCommand(*this);
}

}
