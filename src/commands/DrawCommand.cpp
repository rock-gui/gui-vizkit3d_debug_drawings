#include "DrawCommand.hpp"
#include <vizkit3d_debug_drawings/DrawingManager.hpp>
#include <osgViz/Object.h>
#include <boost/serialization/export.hpp>
namespace vizkit3dDebugDrawings
{
    
DrawCommand::DrawCommand(const std::string& drawingGroupName) : Command(drawingGroupName)
{
    
}


void DrawCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->addPrimitive(getDrawingName(), createPrimitive());
}

DrawCommand::~DrawCommand()
{
}

DrawCommand* DrawCommand::clone() const
{
    //should not be callable, but pure-virtual does not work with orogen.
    throw std::runtime_error("called DrawCommand clone()");
}


}

