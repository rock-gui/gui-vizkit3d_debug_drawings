#include "DrawCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>
#include <osgViz/Object.h>

namespace vizkit3dDebugDrawings
{
    
DrawCommand::DrawCommand(const std::string& drawingName) : drawingName(drawingName)
{
    
}
    
const std::string& DrawCommand::getDrawingName() const
{
    return drawingName;
}

void DrawCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->addPrimitive(drawingName, createPrimitive());
}

DrawCommand::~DrawCommand()
{
}

}