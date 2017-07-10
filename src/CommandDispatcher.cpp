#include <rtt/TaskContext.hpp>
#include "CommandDispatcher.h"
#include "DrawingManager.h"
#include "commands/Command.h"
#include "commands/CommandBuffer.h"
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include <memory>
#include <base/Time.hpp>
#include <base-logging/Logging.hpp>

#include <orocos_cpp/TypeRegistry.hpp>
#include <orocos_cpp/PluginHelper.hpp>
#include <rtt/OutputPort.hpp>
#include <rtt/typelib/TypelibMarshaller.hpp>
#include <rtt/typelib/TypelibMarshallerBase.hpp>
#include <unordered_map>


namespace vizkit3dDebugDrawings
{
    
    
struct CommandDispatcher::Impl
{
    const size_t maxWarnings = 10;
    size_t warningCount = 0; //how many times has the "buffering" warning been shown
    bool configured = false;
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread; //for standalone mode
    std::unique_ptr<DrawingManager> drawingManager; //need to use pointer due to lazy initiaization
    std::deque<std::unique_ptr<vizkit3dDebugDrawings::Command>> beforeConfigCommands; //stores all commands send before config, need to store on heap to store polymorphic copies
    const size_t maxBeforeConfigCommands = 100000; //maximum size of beforeConfigCommands to avoid memory leaks

    RTT::TaskContext* task = nullptr; //used for port mode    
    
    /** boost::shared_ptr pointer is used because we need to send it through a rock port.
     * Sending by value works but would break polymorphism.
     * std::shared_ptr is not used because rtt does not understand it (no c++11 support, yet)*/
    std::unordered_map<std::string, CommandBuffer>  cmdBuffer;
    
    /**drawing names to port mapping */
    std::unordered_map<std::string, RTT::base::OutputPortInterface*> ports; 
    std::unordered_map<std::string, orogen_transports::TypelibMarshallerBase::Handle*> handles; //drawing name to marhaller handle
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
    else if(p->task != nullptr)
    {
        /* Re-sending the complete state instead of just sending the commands 
         * produces some overhead. But depending on the connection type lots of
         * commands may be dropped. If commands are dropped, the current state cannot
         * be reproduced on the other end of the port. Thus we have to send the
         * whole state every time. */
        boost::shared_ptr<Command> pCmd(cmd.clone());
        
        p->cmdBuffer[cmd.getDrawingName()].addCommand(pCmd);
        
        //send with 10hz, sending is slow, otherwise we slow down the task too much
        if((base::Time::now() - p->lastSend).toMilliseconds() >= 100)
        {
            p->lastSend = base::Time::now();
            
            //need to copy because the buffer will switch threads when beeing written to the port.
            //shallow copy is enough, the commands wont be modified.
            //FIXME not sure if we really need to copy anymore since writePort marshalls?! 
            //      Have to figure out if marshaller copys
            boost::shared_ptr<CommandBuffer> copy(new CommandBuffer(p->cmdBuffer[cmd.getDrawingName()]));
            writePort(cmd.getDrawingName(), copy);
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

void CommandDispatcher::configurePort(RTT::TaskContext* taskContext)
{
    checkAndSetConfigured();
    p->task = taskContext;
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


void CommandDispatcher::writePort(const std::string& drawingName, 
                                  boost::shared_ptr<CommandBuffer> buffer)
{
    orogen_transports::TypelibMarshallerBase* marshaller = nullptr;
    orogen_transports::TypelibMarshallerBase::Handle* handle = nullptr;
    RTT::base::OutputPortInterface* port = nullptr;

    const std::string typeName("/boost/shared_ptr</vizkit3dDebugDrawings/CommandBuffer>");
    if(p->ports.find(drawingName) == p->ports.end())
    {
        //FIXME duplicate code from vizkit command
        //FIXME load typeinfo in configure
        //load typeinfo

        RTT::types::TypeInfo* info = RTT::types::TypeInfoRepository::Instance()->type(typeName);
        if(info == nullptr)
        {
            //load typekit if not loaded
            std::string typekitName;
            orocos_cpp::TypeRegistry reg;
            reg.loadTypelist();
            if(!reg.getTypekitDefiningType(typeName, typekitName))
            {
                LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit for: " << typeName;
                return;
            }
            if(!orocos_cpp::PluginHelper::loadTypekitAndTransports(typekitName))
            {
                LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit: " << typekitName;
                return;
            }
            info = RTT::types::TypeInfoRepository::Instance()->type(typeName);
        }    
        assert(info != nullptr);
        
        const std::string portName("debug_" + drawingName);

        port = info->outputPort(portName);    
        if (!port)
        {
            LOG_ERROR_S << "Unable to create port '" << portName << "'";
            return;
        }
        p->task->ports()->addPort(port->getName(), *(port));
        p->ports[drawingName] = port;
        
        marshaller = orogen_transports::getMarshallerFor(typeName);
        handle = marshaller->createHandle();
        p->handles[drawingName] = handle;
    }
    else
    {
        port = p->ports[drawingName];
        marshaller = orogen_transports::getMarshallerFor(typeName);
        handle = p->handles[drawingName];
        //NOTE no need to delete, we use shared_ptr
        //marshaller->deleteOrocosSample(handle);
    }
    
    marshaller->setOrocosSample(handle, &buffer);
    RTT::base::DataSourceBase::shared_ptr dataSource = marshaller->getDataSource(handle);
    port->write(dataSource);
}

}
