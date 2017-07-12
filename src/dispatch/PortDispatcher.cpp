#include <rtt/TaskContext.hpp> //has to be included first FIXME why?
#include "PortDispatcher.hpp"
#include <base-logging/Logging.hpp>
#include <orocos_cpp/PluginHelper.hpp>
#include <orocos_cpp/TypeRegistry.hpp>



namespace vizkit3dDebugDrawings
{
    
PortDispatcher::~PortDispatcher()
{}


PortDispatcher::PortDispatcher(RTT::TaskContext* taskContext) : taskContext(taskContext),
    commandBufferTypeName("/boost/shared_ptr</vizkit3dDebugDrawings/CommandBuffer>"),
    lastSend(base::Time::now())
{
    //load typeinfo
    commandBufferInfo = RTT::types::TypeInfoRepository::Instance()->type(commandBufferTypeName);
    if(commandBufferInfo == nullptr)
    {
        //load typekit if not loaded
        std::string typekitName;
        orocos_cpp::TypeRegistry reg;
        reg.loadTypelist();
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
    
    //by default we flush every 100ms
    const base::Time now = base::Time::now();
    if(now.toMilliseconds() - lastSend.toMilliseconds() >= 100)
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
        
        boost::shared_ptr<CommandBuffer> copy(new CommandBuffer(cmdBuffer[it.first]));
        writePort(it.first, copy);
    }
}


void PortDispatcher::writePort(const std::string& drawingName, boost::shared_ptr< CommandBuffer > buffer)
{
    orogen_transports::TypelibMarshallerBase* marshaller = nullptr;
    orogen_transports::TypelibMarshallerBase::Handle* handle = nullptr;
    RTT::base::OutputPortInterface* port = nullptr;
    
    //create port if it doesnt exist
    if(ports.find(drawingName) == ports.end())
    {
        const std::string portName("debug_" + drawingName);
        //try to get the port (might have been created in another thread)
        port =  dynamic_cast<RTT::base::OutputPortInterface*>(taskContext->ports()->getPort(portName));
        if(port == nullptr)
        {
            //either port does not exist or is not an output port.
            port = commandBufferInfo->outputPort(portName);    
            if (!port)
            {
                LOG_ERROR_S << "Unable to create port '" << portName << "'";
                return;
            }
            taskContext->ports()->addPort(port->getName(), *(port));
        }
        ports[drawingName] = port;
        marshaller = orogen_transports::getMarshallerFor(commandBufferTypeName);
        handle = marshaller->createHandle();
        handles[drawingName] = handle;
    }
    else
    {
        port = ports[drawingName];
        marshaller = orogen_transports::getMarshallerFor(commandBufferTypeName);
        handle = handles[drawingName];
        //NOTE no need to delete, we use shared_ptr
        //marshaller->deleteOrocosSample(handle);
    }
    
    marshaller->setOrocosSample(handle, &buffer);
    RTT::base::DataSourceBase::shared_ptr dataSource = marshaller->getDataSource(handle);
    port->write(dataSource);
}



}