#include "CommandDispatcher.h"
#include "DrawingManager.h"
#include "commands/Command.h"

namespace vizkit3dDebugDrawings
{
void CommandDispatcher::dispatch(const vizkit3dDebugDrawings::Command& cmd)
{
    //FIXME add different dispace modes later
    cmd.execute(DrawingManager::instance());
}
}
