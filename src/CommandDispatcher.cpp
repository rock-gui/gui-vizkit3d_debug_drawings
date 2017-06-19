#include "CommandDispatcher.h"
#include "DrawingManager.h"
#include "commands/Command.h"
#include "commands/CommandBuffer.h"
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include <memory>
#include <base/Time.hpp>

namespace vizkit3dDebugDrawings
{
    
    
struct CommandDispatcher::Impl
{
    /** Sending the state through a port is expensive and laggy. Therefore we limit
     *  how often data will be send through the port. sendDelay is the time between
     *  two send operations in ms*/
    const int sendDelay = 33;
    const int maxWarnings = 10;
    size_t warningCount = 0; //how many times has the "buffering" warning been shown
    bool configured = false;
    RTT::OutputPort<boost::shared_ptr<CommandBuffer>>* port = nullptr; //for port mode
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread; //for standalone mode
    std::unique_ptr<DrawingManager> drawingManager; //need to use pointer due to lazy initiaization
    std::deque<std::unique_ptr<vizkit3dDebugDrawings::Command>> beforeConfigCommands; //stores all commands send before config, need to store on heap to store polymorphic copies
    const size_t maxBeforeConfigCommands = 100000; //maximum size of beforeConfigCommands to avoid memory leaks
    boost::shared_ptr<CommandBuffer> cmdBuffer; //is pointer because we need to send it through port (sending by value works but would break polymorphism)
    base::Time lastSend = base::Time::now();
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
        /* Re-sending the complete state instead of just sending the commands 
         * produces some overhead. But depending on the connection type lots of
         * commands may be dropped. If commands are dropped, the current state cannot
         * be reproduced on the other end of the port. Thus we have to send the
         * whole state every time. */
        boost::shared_ptr<Command> pCmd(cmd.clone());
        p->cmdBuffer->addCommand(pCmd);
        
        if(base::Time::now() - p->lastSend > base::Time::fromMilliseconds(p->sendDelay))
        {
            p->lastSend = base::Time::now();
            
            //need to copy because the buffer will switch threads when beeing written to the port.
            //shallow copy is enough, the commands wont be modified.
            boost::shared_ptr<CommandBuffer> copy(new CommandBuffer(*(p->cmdBuffer)));
            p->port->write(copy);
        }
    }
    else if(!p->configured)
    {
        if(p->warningCount < p->maxWarnings)
        {
            std::cout << "Warning: Debug drawings not configured. Buffering drawings until configured.\n";
            ++p->warningCount;
        }
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

void CommandDispatcher::configurePort(RTT::OutputPort<boost::shared_ptr<CommandBuffer>>* port)
{
    checkAndSetConfigured();
    p->port = port;
    p->cmdBuffer.reset(new CommandBuffer);
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
    std::cout << "DISPATCHING BUFFERED COMMANDS\n";
    assert(p->configured);
    for(const std::unique_ptr<vizkit3dDebugDrawings::Command>& cmd : p->beforeConfigCommands)
    {
        dispatch(*cmd);
    }
    p->beforeConfigCommands.clear();
}

bool CommandDispatcher::isConfigured() const
{
    return p->configured;
}

vizkit3d::Vizkit3DWidget* CommandDispatcher::getWidget()
{
    if(!isConfigured())
        throw std::runtime_error("Debug drawings not configured");
    
    if(!(p->drawingManager))
        throw std::runtime_error("Debug drawigns not configured to use widget");

    return p->drawingManager->getVizkit3DWidget();
}




}
