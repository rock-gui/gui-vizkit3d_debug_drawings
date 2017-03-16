#include "RemoveDrawingCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>


namespace vizkit3dDebugDrawings
{
void RemoveDrawingCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->removeDrawing(getDrawingName());
}

RemoveDrawingCommand::RemoveDrawingCommand(const std::string& drawingName) :
        Command(drawingName)
{}

RemoveDrawingCommand::RemoveDrawingCommand() : Command("default")
{}


RemoveDrawingCommand::~RemoveDrawingCommand()
{}

RemoveDrawingCommand* RemoveDrawingCommand::clone() const
{
    return new RemoveDrawingCommand(*this);
}

}

