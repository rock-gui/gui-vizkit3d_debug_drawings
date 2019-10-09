#include "StandaloneDispatcher.hpp"
#include "../commands/Command.hpp"

namespace vizkit3dDebugDrawings
{
    
StandaloneDispatcher::StandaloneDispatcher()
{
    thread.start();
    drawingManager.reset(new DrawingManager(thread.getWidget()));
}
    
void StandaloneDispatcher::flush()
{}
    
void StandaloneDispatcher::dispatch(const Command& cmd)
{
    cmd.execute(drawingManager.get());
}

}
