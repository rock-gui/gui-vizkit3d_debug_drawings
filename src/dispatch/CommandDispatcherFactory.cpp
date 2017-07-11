#include "CommandDispatcherFactory.hpp"
#include "PortDispatcher.hpp"
#include "StandaloneDispatcher.hpp"
#include "ExistingWidgetDispatcher.hpp"
#include <stdexcept>

namespace vizkit3dDebugDrawings
{

thread_local std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::dispatcher = nullptr;
    
void CommandDispatcherFactory::createPortDispatcher(RTT::TaskContext* taskContext)
{
    if(instanceExists())
    {
        throw std::runtime_error("dispatcher already created");
    }
    dispatcher.reset(new PortDispatcher(taskContext));
}

void CommandDispatcherFactory::createStandaloneDispatcher()
{
    if(instanceExists())
    {
        throw std::runtime_error("dispatcher already created");
    }
    dispatcher.reset(new StandaloneDispatcher());
}


void CommandDispatcherFactory::createWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget)
{
    if(instanceExists())
    {
        throw std::runtime_error("dispatcher already created");
    }
    dispatcher.reset(new ExistingWidgetDispatcher(widget));
}

std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::getThreadLocalInstance()
{
    if(dispatcher)
    {
        return dispatcher;
    }
    throw std::runtime_error("Dispatcher not created");
}

bool CommandDispatcherFactory::instanceExists()
{
    return dispatcher != nullptr;
}


}