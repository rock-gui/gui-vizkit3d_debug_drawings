#include "ClearDrawingCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>

namespace vizkit3dDebugDrawings
{
ClearDrawingCommand::ClearDrawingCommand(const std::string& drawingName) :
        drawingName(drawingName)
{}

ClearDrawingCommand::ClearDrawingCommand() : drawingName("default")
{

}


void ClearDrawingCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->clearDrawing(drawingName);
}

ClearDrawingCommand::~ClearDrawingCommand()
{}

ClearDrawingCommand* ClearDrawingCommand::clone() const
{
    return new ClearDrawingCommand(*this);
}


}