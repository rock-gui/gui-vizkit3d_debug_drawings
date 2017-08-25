#include "ICommandDispatcher.hpp"
#include <unordered_map>
#include <string>
#include "../commands/CommandBuffer.h" //FIXME relative include
#include <base/Time.hpp>

namespace RTT
{
    class TaskContext;
    namespace base
    {
        class OutputPortInterface;
    }
}


namespace vizkit3dDebugDrawings
{

class CommandBuffer;
    
class PortDispatcher : public ICommandDispatcher
{
public:
    PortDispatcher(RTT::TaskContext* taskContext);
    virtual ~PortDispatcher();
    
    virtual void dispatch(const Command& cmd);
    
    virtual void flush();
    
private:
    
    void writePort(const std::string& drawingName, 
                   boost::shared_ptr<CommandBuffer> buffer);
    
    RTT::TaskContext* taskContext;//context in which ports will be created
    std::unordered_map<std::string, RTT::base::OutputPortInterface*> ports; //drawing name to port mapping
    std::unordered_map<std::string, CommandBuffer>  cmdBuffer;
    base::Time lastSend;
};
    
}