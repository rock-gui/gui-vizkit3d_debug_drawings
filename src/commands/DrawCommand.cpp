#include "DrawCommand.hpp"
#include "DrawingManager.hpp"
#include <osgViz/Object.h>
#include <boost/serialization/export.hpp>
namespace vizkit3dDebugDrawings
{
    
DrawCommand::DrawCommand(const std::string& drawingChannel) : Command(drawingChannel)
{
    
}


void DrawCommand::execute(DrawingManager* drawingManager) const
{
    drawingManager->addPrimitive(getDrawingChannel(), createPrimitive());
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

