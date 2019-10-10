#include <rtt/TaskContext.hpp> //has to be included first FIXME why?
#include "PortDispatcher.hpp"
#include <rtt/OutputPort.hpp>
#include <iostream>



//TODO locking is very simple right now. If this becomes a problem turn this into an active thread

namespace vizkit3dDebugDrawings
{
    
PortDispatcher::~PortDispatcher()
{}


PortDispatcher::PortDispatcher() : lastSend(std::chrono::system_clock::now())
{}


void PortDispatcher::registerDrawingNamesWithTask(RTT::TaskContext* taskContext, std::vector<std::string>drawingGroupNames)
{
    std::lock_guard<std::mutex> lock(drawingNames2TasksMutex);
    
    for(const std::string& drawingName : drawingGroupNames)
    {
        //TODO figure out a way to support multiple tasks using the same drawing name?
        //     Is that even possible?
        if(drawingNames2Tasks.find(drawingName) != drawingNames2Tasks.end())
        {
            throw std::runtime_error("Drawing '" + drawingName + "' has already been registered to Task '" + taskContext->getName() + "'");
        }
        drawingNames2Tasks[drawingName] = taskContext;
        createPort(drawingName, taskContext);
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
    
    {
        std::lock_guard<std::mutex> lock(cmdBufferMutex);
        cmdBuffer[cmd.getDrawingName()].addCommand(pCmd);
    }
    
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
    std::lock_guard<std::mutex> lock(cmdBufferMutex);
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


void PortDispatcher::createPort(const std::string& drawingGroupName, RTT::TaskContext* taskContext)
{
    
    //TODO think about if there is a better way to handle this case?
    if(drawingNames2Tasks.find(drawingGroupName) == drawingNames2Tasks.end())
    {
        std::cout << "WARNING: No task registered for debug drawing '" <<  drawingGroupName << "'. Drawing IGNORED!" << std::endl;
        return;
    }
    
    //only create port if we havent created it before
    //FIXME this happens when multiple ports use the same drawing name
    if(ports.find(drawingGroupName) != ports.end())
    {
        std::cout << "ERROR: Tried to create port for drawing '" << drawingGroupName << "' but port already exists" << std::endl;
        return;
    }
    
    const std::string portName("debug_" + drawingGroupName);
    //check if someone else has created the port, the user might have created the port manually on the orogen file
    //if yes use it, if not create it
    RTT::base::OutputPortInterface* port =  dynamic_cast<RTT::base::OutputPortInterface*>(taskContext->ports()->getPort(portName));
    if(port == nullptr)
    {
        auto typedPort = new RTT::OutputPort<boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>>(portName, true);
        port = typedPort;
        taskContext->ports()->addPort(port->getName(), *(port));
    }
    ports[drawingGroupName] = port;   
}


void PortDispatcher::writePort(const std::string& drawingGroupName, boost::shared_ptr< CommandBuffer > buffer)
{   
    const auto &it = ports.find(drawingGroupName);
    //create port if it doesnt exist
    if(it == ports.end())
    {
        std::cout << "ERROR: Port for drawing '" <<  drawingGroupName << "' does not exist" << std::endl;
        return;
    }
    
    auto typedPort = dynamic_cast<RTT::OutputPort<boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer>> *>(it->second);
    typedPort->write(buffer);
}



}
