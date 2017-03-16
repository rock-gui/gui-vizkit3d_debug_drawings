#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>
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
        }
        
    public:
        void addCommand(boost::shared_ptr<Command> cmd);
        void executeAll(DrawingManager* manager) const;
        const std::unordered_map<std::string, std::vector<boost::shared_ptr<Command>>>& getCommands() const;
        
    private:
        std::unordered_map<std::string, std::vector<boost::shared_ptr<Command>>> commands;
    };
}

