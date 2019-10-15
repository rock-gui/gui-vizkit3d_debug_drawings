#include "Command.hpp"
#include <stdexcept>

namespace vizkit3dDebugDrawings
{
void Command::execute(vizkit3dDebugDrawings::DrawingManager* drawingManager) const
{
    //NOTE This method should be pure virtual, however pure virtual classes cannot
    //     be used in orogen.
    throw std::runtime_error("called base class execute()");
}

Command* Command::clone() const
{
    //NOTE This method should be pure virtual, however pure virtual classes cannot
    //     be used in orogen.
    throw std::runtime_error("called base class clone()");
}

const std::string& Command::getDrawingChannel() const
{
    return drawingChannel;
}

Command::Command(const std::string& drawingChannel) : drawingChannel(drawingChannel)
{
    
}
Command::Command() : drawingChannel("default")
{

}



Command::~Command()
{
}

}

