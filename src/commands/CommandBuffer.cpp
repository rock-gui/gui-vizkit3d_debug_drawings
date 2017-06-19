#include "CommandBuffer.h"
#include "Command.h"
#include "DrawCommand.h"
#include "ClearDrawingCommand.h"
#include "RemoveDrawingCommand.h"
#include "ClearPlotCommand.h"
#include <vizkit3d_debug_drawings/DrawingManager.h>

//need to be included. otherwise BOOST_CLASS_EXPORT wont work (http://www.boost.org/doc/libs/1_46_1/libs/serialization/doc/special.html)
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "BoostSerializationExports.h"
using namespace vizkit3dDebugDrawings;

void CommandBuffer::addCommand(boost::shared_ptr<Command> cmd)
{
    ClearDrawingCommand* clearCmd = nullptr;
    RemoveDrawingCommand* removeCmd = nullptr;
    ClearPlotCommand* clearPlotCmd = nullptr;
    

    if((clearCmd = dynamic_cast<ClearDrawingCommand*>(cmd.get())))
    {
        commands[clearCmd->getDrawingName()].clear();
    }
    else if((removeCmd = dynamic_cast<RemoveDrawingCommand*>(cmd.get())))
    {
        commands[removeCmd->getDrawingName()].clear();
    }
    else if(clearPlotCmd = dynamic_cast<ClearPlotCommand*>(cmd.get()))
    {
        commands[clearPlotCmd->getDrawingName()].clear();
    }

    commands[cmd->getDrawingName()].push_back(cmd);
}

void CommandBuffer::executeAll(vizkit3dDebugDrawings::DrawingManager* manager) const
{
    
    for(const auto& it : commands)
    {
        for(const auto& cmd : it.second)
        {
            cmd->execute(manager);
        }
    }
}

const CommandBuffer::CommandMap& CommandBuffer::getCommands() const
{
    return commands;
}



BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::CommandBuffer);

