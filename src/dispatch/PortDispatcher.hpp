#include "ICommandDispatcher.hpp"
#include <unordered_map>
#include <string>
#include "../commands/CommandBuffer.hpp" //FIXME relative include
#include <chrono>
#include <mutex>

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
    
/** Uses rock ports as drawing channels.
 * 
 */
class PortDispatcher : public ICommandDispatcher
{
public:
    PortDispatcher();
    virtual ~PortDispatcher();
    
    virtual void dispatch(const Command& cmd);
    
    virtual void flush();

    /** FIXME TODO COMMENT */
    virtual void registerDrawingChannelsWithTask(RTT::TaskContext* taskContext, std::vector<std::string>drawingChannels);
    
private:
    
    void writePort(const std::string& drawingChannel, 
                   boost::shared_ptr<CommandBuffer> buffer);
    
    /** Create a port with name "debug_[drawingChannel]" on the @p taskContext */
    void createPort(const std::string& drawingChannel, RTT::TaskContext* taskContext);
    
    std::unordered_map<std::string, RTT::TaskContext*> drawingNames2Tasks; //maps each drawing name to a task
    std::unordered_map<std::string, RTT::base::OutputPortInterface*> ports; //drawing name to port mapping
    std::unordered_map<std::string, CommandBuffer>  cmdBuffer;
    std::chrono::system_clock::time_point lastSend;
    std::mutex drawingNames2TasksMutex;
    std::mutex cmdBufferMutex;
};
    
}
