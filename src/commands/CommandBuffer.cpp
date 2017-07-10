#include "CommandBuffer.h"
#include "Command.h"
#include "DrawCommand.h"
#include "ClearDrawingCommand.h"
#include "RemoveDrawingCommand.h"
#include "ClearPlotCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>
#include <base-logging/Logging.hpp>

//need to be included. otherwise BOOST_CLASS_EXPORT wont work (http://www.boost.org/doc/libs/1_46_1/libs/serialization/doc/special.html)
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "BoostSerializationExports.h"

using namespace vizkit3dDebugDrawings;

CommandBuffer::CommandBuffer(size_t maxBufferSize) : maxBufferSize(maxBufferSize)
{
    std::cout << "COMMAND_BUFFER CREATED\n";
}

CommandBuffer::CommandBuffer() : maxBufferSize(50000)
{
    std::cout << "COMMAND_BUFFER CREATED 22\n";
}

CommandBuffer::~CommandBuffer()
{
    std::cout << "DELETE BUFFER\n";
}



void CommandBuffer::addCommand(boost::shared_ptr<Command> cmd)
{
    ClearDrawingCommand* clearCmd = nullptr;
    RemoveDrawingCommand* removeCmd = nullptr;
    ClearPlotCommand* clearPlotCmd = nullptr;
    

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
        LOG_WARN_S << "Commandbuffer is full. Dropping old commands."; 
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

