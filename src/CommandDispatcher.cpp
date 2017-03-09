#include "CommandDispatcher.h"
#include "DrawingManager.h"
#include "commands/Command.h"
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include <memory>

namespace vizkit3dDebugDrawings
{
    
    
struct CommandDispatcher::Impl
{
    bool configured = false;
    RTT::OutputPort<Command>* port = nullptr; //for port mode
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread; //for standalone mode
    std::unique_ptr<DrawingManager> drawingManager; //need to use pointer due to lazy initiaization
    std::deque<std::unique_ptr<vizkit3dDebugDrawings::Command>> beforeConfigCommands; //stores all commands send before config, need to store on heap to store polymorphic copies
    const size_t maxBeforeConfigCommands = 100000; //maximum size of beforeConfigCommands to avoid memory leaks
};

CommandDispatcher::CommandDispatcher() : p(new CommandDispatcher::Impl())
{
    
}

CommandDispatcher::~CommandDispatcher()
{
    if(p != nullptr)
    {
        delete p;
        p = nullptr;
    }
    
}


CommandDispatcher* CommandDispatcher::threadLocalInstance()
{
    static thread_local CommandDispatcher dispatcher;
    return &dispatcher;
}


void CommandDispatcher::dispatch(const vizkit3dDebugDrawings::Command& cmd)
{
    if(p->drawingManager != nullptr)
    {
        //either standalone or widget mode
        cmd.execute(p->drawingManager.get());
    }
    else if(p->port != nullptr)
    {
        p->port->write(cmd);
    }
    else if(!p->configured)
    {
        p->beforeConfigCommands.emplace_back(cmd.clone());
        if(p->beforeConfigCommands.size() >= p->maxBeforeConfigCommands)
        {
            p->beforeConfigCommands.pop_front();
        }
    }
    else
    {
        assert(false); //cannot happen if there is no logic error in the code
    }
}

void CommandDispatcher::configurePort(RTT::OutputPort< Command >* port)
{
    checkAndSetConfigured();
    p->port = port;
    dispatchBufferedCommands();
}

void CommandDispatcher::configureStandalone()
{
    checkAndSetConfigured();
    p->thread.start();
    p->drawingManager.reset(new DrawingManager(p->thread.getWidget()));
    dispatchBufferedCommands();
}

void CommandDispatcher::configureUseWidget(vizkit3d::Vizkit3DWidget* widget)
{
    checkAndSetConfigured();
    p->drawingManager.reset(new DrawingManager(widget));
    dispatchBufferedCommands();
}

void CommandDispatcher::checkAndSetConfigured()
{
    if(p->configured)
    {
        throw std::runtime_error("debug drawings already configured");
    }
    p->configured = true;    
}

void CommandDispatcher::dispatchBufferedCommands()
{
    assert(p->configured);
    for(const std::unique_ptr<vizkit3dDebugDrawings::Command>& cmd : p->beforeConfigCommands)
    {
        dispatch(*cmd);
    }
    p->beforeConfigCommands.clear();
}

}
