#include "CommandDispatcherFactory.hpp"
#include "StandaloneDispatcher.hpp"
#include "ExistingWidgetDispatcher.hpp"

#ifdef USE_PORTS
  #include "PortDispatcher.hpp"
#endif

#include <stdexcept>

namespace vizkit3dDebugDrawings
{

std::shared_ptr<ICommandDispatcher> CommandDispatcherFactory::dispatcher = nullptr;
std::mutex CommandDispatcherFactory::createMutex;
    
#ifdef USE_PORTS
void CommandDispatcherFactory::createPortDispatcher(RTT::TaskContext* taskContext, std::vector<std::string> drawingGroupNames)
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
    portDisp->registerDrawingNamesWithTask(taskContext, drawingGroupNames);

}
#endif

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
