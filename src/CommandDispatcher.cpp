#include "CommandDispatcher.h"
#include "DrawingManager.h"
#include "commands/Command.h"

namespace vizkit3dDebugDrawings
{
    
thread_local RTT::OutputPort<Command>* CommandDispatcher::port = nullptr;

void CommandDispatcher::dispatch(const vizkit3dDebugDrawings::Command& cmd)
{
    if(port == nullptr)
    {
        //execute on local instance of DrawingManager
        cmd.execute(DrawingManager::instance());
    }
    else
    {
        port->write(cmd);
    }
}

void CommandDispatcher::setPort(RTT::OutputPort< Command >* _port)
{
    port = _port;
}


}
