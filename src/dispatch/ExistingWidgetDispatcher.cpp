#include "ExistingWidgetDispatcher.hpp"
#include "../commands/Command.h"

namespace vizkit3dDebugDrawings
{
    
ExistingWidgetDispatcher::ExistingWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget) :
    drawingManager(widget)
{}

ExistingWidgetDispatcher::~ExistingWidgetDispatcher()
{}


void ExistingWidgetDispatcher::flush()
{}

    
void ExistingWidgetDispatcher::dispatch(const Command& cmd)
{
    cmd.execute(&drawingManager);
}

}