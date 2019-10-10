#include "ICommandDispatcher.hpp"
#include <unordered_map>
#include <string>
#include "../commands/CommandBuffer.hpp" //FIXME relative include
#include <chrono>

namespace RTT
{
    class TaskContext;
    namespace base
    {
        class OutputPortInterface;
    }
}

//FIXME make threadsafe!

namespace vizkit3dDebugDrawings
{

class CommandBuffer;
    
class PortDispatcher : public ICommandDispatcher
{
public:
    PortDispatcher();
    virtual ~PortDispatcher();
    
    virtual void dispatch(const Command& cmd);
    
    virtual void flush();

    virtual void registerDrawingNamesWithTask(RTT::TaskContext* taskContext, std::vector<std::string>drawingGroupNames);
    
private:
    
    void writePort(const std::string& drawingGroupName, 
                   boost::shared_ptr<CommandBuffer> buffer);
    
    std::unordered_map<std::string, RTT::TaskContext*> drawingNames2Tasks; //maps each drawing name to a task
    std::unordered_map<std::string, RTT::base::OutputPortInterface*> ports; //drawing name to port mapping
    std::unordered_map<std::string, CommandBuffer>  cmdBuffer;
    std::chrono::system_clock::time_point lastSend;
};
    
}
