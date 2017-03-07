#pragma once
#include <rtt/OutputPort.hpp>
#include "commands/Command.h"

namespace vizkit3dDebugDrawings
{
    
    /** Dispatches commands to a port or a local drawing manager.
     *  By default a local drawing manager is used*/
    class CommandDispatcher
    {
    public:
        static void dispatch(const Command& cmd);
        
        /**If a port is set, the dispatcher will dispatch the commands through
         * that port. The port can be set once from each thread/process. 
         * By default no port is set. In that case the dispatcher will dispatch the 
         * commands to its internal DrawingManager*/
        static void setPort(RTT::OutputPort<Command>* port);
        
    private:
        /**If this port is set, the dispatcher will dispatch the commands through
         * the port instead of using the internal DrawingManager.*/
        static thread_local RTT::OutputPort<Command>* port;
    };
}