#include "CommandBuffer.hpp"
#include "Command.hpp"
#include "DrawCommand.hpp"
#include "ClearDrawingCommand.hpp"
#include "RemoveDrawingCommand.hpp"
#include "ClearPlotCommand.hpp"
#include "vizkit3d_debug_drawings/DrawingManager.hpp"

//need to be included. otherwise BOOST_CLASS_EXPORT wont work (http://www.boost.org/doc/libs/1_46_1/libs/serialization/doc/special.html)
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "BoostSerializationExports.hpp"

using namespace vizkit3dDebugDrawings;

CommandBuffer::CommandBuffer(size_t maxBufferSize) : maxBufferSize(maxBufferSize)
{
}

CommandBuffer::CommandBuffer() : maxBufferSize(50000)
{
}



void CommandBuffer::addCommand(boost::shared_ptr<Command> cmd)
{
    if(dynamic_cast<ClearDrawingCommand*>(cmd.get()) || 
       dynamic_cast<RemoveDrawingCommand*>(cmd.get()) ||
       dynamic_cast<ClearPlotCommand*>(cmd.get()))
    {
        commands.clear();
    }

    commands.push_back(cmd);
    if(commands.size() > maxBufferSize)
    {
        commands.pop_front();
        std::cerr << "Commandbuffer is full. Dropping old commands."; 
    }
}

void CommandBuffer::executeAll(vizkit3dDebugDrawings::DrawingManager* manager) const
{
    
    for(const auto& cmd : commands)
    {
        cmd->execute(manager); 
    }
}

const std::deque<boost::shared_ptr<Command>>& CommandBuffer::getCommands() const
{
    return commands;
}



BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::CommandBuffer);

