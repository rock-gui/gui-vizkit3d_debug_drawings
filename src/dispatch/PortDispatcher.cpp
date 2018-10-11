#include <rtt/TaskContext.hpp> //has to be included first FIXME why?
#include "PortDispatcher.hpp"
#include <base-logging/Logging.hpp>
#include <orocos_cpp/PluginHelper.hpp>
#include <orocos_cpp/TypeRegistry.hpp>
#include <rtt/OutputPort.hpp>


namespace vizkit3dDebugDrawings
{
    
PortDispatcher::~PortDispatcher()
{}


PortDispatcher::PortDispatcher(RTT::TaskContext* taskContext) : taskContext(taskContext),    
    lastSend(base::Time::now())
{
    std::string commandBufferTypeName("/boost/shared_ptr</vizkit3dDebugDrawings/CommandBuffer>");
    //load typeinfo
    RTT::types::TypeInfo *commandBufferInfo = RTT::types::TypeInfoRepository::Instance()->type(commandBufferTypeName);
    if(commandBufferInfo == nullptr)
    {
        //load typekit if not loaded
        std::string typekitName;
        orocos_cpp::TypeRegistry reg;
        reg.loadTypeRegistries();
        if(!reg.getTypekitDefiningType(commandBufferTypeName, typekitName))
        {
            LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit for: " << commandBufferTypeName;
            return;
        }
        if(!orocos_cpp::PluginHelper::loadTypekitAndTransports(typekitName))
        {
            LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit: " << typekitName;
            return;
        }
        commandBufferInfo = RTT::types::TypeInfoRepository::Instance()->type(commandBufferTypeName);
    }    
    assert(commandBufferInfo != nullptr);
}

    
void PortDispatcher::dispatch(const Command& cmd)
{
    
    /* Re-sending the complete state instead of just sending the commands 
    * produces some overhead. But depending on the connection type lots of
    * commands may be dropped. If commands are dropped, the current state cannot
    * be reproduced on the other end of the port. Thus we have to send the
    * whole state every time. */
    boost::shared_ptr<Command> pCmd(cmd.clone());

    cmdBuffer[cmd.getDrawingName()].addCommand(pCmd);
    
    //by default we flush every 1.5 seconds
    //call flush manually if you want faster updates
    const base::Time now = base::Time::now();
    if(now.toMilliseconds() - lastSend.toMilliseconds() >= 1500)
    {
        lastSend = now;
        flush();
    }
}

void PortDispatcher::flush()
{
    for(auto it : cmdBuffer)
    {
        //need to copy because the buffer will switch threads when beeing written to the port.
        //shallow copy is enough, the commands wont be modified.
        //FIXME not sure if we really need to copy anymore since writePort marshalls?! 
        //      Have to figure out if marshaller copys
        
        boost::shared_ptr<CommandBuffer> copy(new CommandBuffer(it.second));
        writePort(it.first, copy);
    }
}


void PortDispatcher::writePort(const std::string& drawingGroupName, boost::shared_ptr< CommandBuffer > buffer)
{
    RTT::OutputPort<boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>> *typedPort;
    
    const auto &it = ports.find(drawingGroupName);
    
    //create port if it doesnt exist
    if(it == ports.end())
    {
        RTT::base::OutputPortInterface* port = nullptr;
        const std::string portName("debug_" + drawingGroupName);
        //try to get the port (might have been created in another thread)
        port =  dynamic_cast<RTT::base::OutputPortInterface*>(taskContext->ports()->getPort(portName));
        if(port == nullptr)
        {
            typedPort = new RTT::OutputPort<boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>>(portName, true);
            port = typedPort;
            taskContext->ports()->addPort(port->getName(), *(port));
        }
        else
        {
            typedPort = dynamic_cast<RTT::OutputPort<boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>> *>(port);
        }
        ports[drawingGroupName] = port;
    }
    else
    {
        typedPort = dynamic_cast<RTT::OutputPort<boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>> *>(it->second);
    }
    
    typedPort->write(buffer);
}



}