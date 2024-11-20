#include "CommandDispatcherFactory.hpp"
#ifndef DISABLE_QT_BUILD
#include "StandaloneDispatcher.hpp"
#include "ExistingWidgetDispatcher.hpp"
#endif

#ifdef USE_PORTS
  #include "PortDispatcher.hpp"
#endif

#include <stdexcept>

namespace vizkit3dDebugDrawings
{

std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::dispatcher = nullptr;
std::mutex CommandDispatcherFactory::createMutex;
    
#ifdef USE_PORTS
void CommandDispatcherFactory::createPortDispatcher(RTT::TaskContext* taskContext,const std::vector<std::string>& drawingChannels)
{
    //this is a little bit of a hack. 
    //in reality there is only one port dispatcher. This dispatcher works for all ports across all task threads.
    std::lock_guard<std::mutex> lock(createMutex);
    if(!instanceExists())
    {
        dispatcher.reset(new PortDispatcher());
    }
    
    std::shared_ptr<PortDispatcher> portDisp = std::dynamic_pointer_cast<PortDispatcher>(dispatcher);
    
    if(!portDisp)
    {
        throw std::runtime_error("vizkit3d_debug_drawings: current dispatcher is not a port dispatcher");
    }
    portDisp->registerDrawingChannelsWithTask(taskContext, drawingChannels);

}
#endif

#ifndef DISABLE_QT_BUILD
void CommandDispatcherFactory::createStandaloneDispatcher()
{
    std::lock_guard<std::mutex> lock(createMutex);
    if(!instanceExists())
    {
        dispatcher.reset(new StandaloneDispatcher());
    }
    else
    {
        std::cout << "WARNING: CommandDispatcherFactory::createStandaloneDispatcher() called multiple times" << std::endl;
    }
}


void CommandDispatcherFactory::createWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget)
{
    std::lock_guard<std::mutex> lock(createMutex);
    if(!instanceExists())
    {
        dispatcher.reset(new ExistingWidgetDispatcher(widget));
    }
    else
    {
        std::cout << "WARNING: CommandDispatcherFactory::createWidgetDispatcher() called multiple times" << std::endl;
    }
}
#endif

std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::getInstance()
{
    if(dispatcher)
    {
        return dispatcher;
    }
    throw std::runtime_error("vizkit3d_debug_drawings: Dispatcher not created.\n Are you invoking debug drawing methods from a different thread?");
}

bool CommandDispatcherFactory::instanceExists()
{
    return dispatcher != nullptr;
}


}
