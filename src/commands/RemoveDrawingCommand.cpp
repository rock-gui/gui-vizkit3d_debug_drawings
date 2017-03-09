#include "RemoveDrawingCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>


namespace vizkit3dDebugDrawings
{
void RemoveDrawingCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->removeDrawing(drawingName);
}

RemoveDrawingCommand::RemoveDrawingCommand(const std::string& drawingName) :
        drawingName(drawingName)
{}

RemoveDrawingCommand::~RemoveDrawingCommand()
{}

RemoveDrawingCommand* RemoveDrawingCommand::clone() const
{
    return new RemoveDrawingCommand(*this);
}



}