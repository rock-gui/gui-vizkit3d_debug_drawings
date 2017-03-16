#include "ClearDrawingCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>


namespace vizkit3dDebugDrawings
{
ClearDrawingCommand::ClearDrawingCommand(const std::string& drawingName) :
        Command(drawingName)
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
