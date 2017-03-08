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
    RTT::OutputPort< Command >* port = nullptr; //for port mode
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread; //for standalone mode
    std::unique_ptr<DrawingManager> drawingManager; //need to use pointer due to lazy initiaization
    
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
        //TODO buffer commands
        throw std::runtime_error("not implemented, yet");
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
}

void CommandDispatcher::configureStandalone()
{
    checkAndSetConfigured();
    p->thread.start();
    p->drawingManager.reset(new DrawingManager(p->thread.getWidget()));
}

void CommandDispatcher::configureUseWidget(vizkit3d::Vizkit3DWidget* widget)
{
    checkAndSetConfigured();
    p->drawingManager.reset(new DrawingManager(widget));
}


void CommandDispatcher::checkAndSetConfigured()
{
    if(p->configured)
    {
        throw std::runtime_error("debug drawings already configured");
    }
    p->configured = true;    
}
}
