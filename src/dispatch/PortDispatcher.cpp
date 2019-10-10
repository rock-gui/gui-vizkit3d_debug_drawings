#include <rtt/TaskContext.hpp> //has to be included first FIXME why?
#include "PortDispatcher.hpp"
#include <rtt/OutputPort.hpp>
#include <iostream>



namespace vizkit3dDebugDrawings
{
    
PortDispatcher::~PortDispatcher()
{}


PortDispatcher::PortDispatcher() : lastSend(std::chrono::system_clock::now())
{}


void PortDispatcher::registerDrawingNamesWithTask(RTT::TaskContext* taskContext, std::vector<std::string>drawingGroupNames)
{
    for(const std::string& drawingName : drawingGroupNames)
    {
        //TODO figure out a way to support multiple tasks using the same drawing name?
        //     Is that even possible?
        if(drawingNames2Tasks.find(drawingName) != drawingNames2Tasks.end())
        {
            throw std::runtime_error("Drawing '" + drawingName + "' has already been registered to Task '" + taskContext->getName() + "'");
        }
        drawingNames2Tasks[drawingName] = taskContext;
    }
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
    const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    if(now - lastSend >= std::chrono::milliseconds(1500))
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
    
    
    //TODO think about if there is a better way to handle this case?
    if(drawingNames2Tasks.find(drawingGroupName) == drawingNames2Tasks.end())
    {
        std::cout << "WARNING: No task registered for debug drawing '" <<  drawingGroupName << "'. Drawing IGNORED!" << std::endl;
        return;
    }
    
    //create port if it doesnt exist
    if(it == ports.end())
    {
        RTT::base::OutputPortInterface* port = nullptr;
        const std::string portName("debug_" + drawingGroupName);
        //try to get the port (might have been created in another thread)
        
        RTT::TaskContext* taskContext = drawingNames2Tasks[drawingGroupName];
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
