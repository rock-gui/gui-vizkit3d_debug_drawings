#pragma once

namespace vizkit3dDebugDrawings
{

class Command;
    
class ICommandDispatcher
{
public:
    /** Dispatch the given drawing command.*/
    virtual void dispatch(const Command& cmd) = 0;
    
    /**Dispatchers may buffer commands until some internal limit is reached.
     * Call this method to force dispatching the buffer even though it is not full.*/
    virtual void flush() = 0;
    
    virtual ~ICommandDispatcher(){}
};
}