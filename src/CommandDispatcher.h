#pragma once

namespace vizkit3dDebugDrawings
{
    class Command;
    
    /** Dispatches commands to a port or a local drawing manager.
     *  By default a local drawing manager is used*/
    class CommandDispatcher
    {
    public:
        static void dispatch(const Command& cmd);
    };
}