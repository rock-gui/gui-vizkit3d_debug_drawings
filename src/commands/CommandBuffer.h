#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/archive/basic_archive.hpp> //needed by boost/serialization/deque.hpp
#include <boost/serialization/access.hpp>
#include <boost/serialization/deque.hpp>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include "Command.h" //needs to be included for serialization to work :/

namespace vizkit3dDebugDrawings
{
    class DrawingManager;
    
    /** Intelligent buffer for commands.
     *  Obsolet commands are removed from the buffer to reduce buffer size.*/
    class CommandBuffer
    {
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & commands;
            ar & maxBufferSize;
        }
        
    public:

        CommandBuffer(); //for use in boost serialization only
        CommandBuffer(size_t maxBufferSize);
        
        void addCommand(boost::shared_ptr<Command> cmd);
        void executeAll(DrawingManager* manager) const;
        
        const std::deque<boost::shared_ptr<Command>>& getCommands() const;

                
    private:
        std::deque<boost::shared_ptr<Command>> commands;
        size_t maxBufferSize; //FIXME should be const but serialization breaks (i.e. doesnt compile) if it is const
    };
}

