#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

#if BOOST_VERSION < 105600
    #include <map>
    #include <boost/serialization/map.hpp>
#else
    #include <unordered_map>
    #include <boost/serialization/unordered_map.hpp>
#endif

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
        
#if BOOST_VERSION < 105600
        using CommandMap = std::map<std::string, std::vector<boost::shared_ptr<Command>>>;
#else
        using CommandMap = std::unordered_map<std::string, std::vector<boost::shared_ptr<Command>>>;
#endif   
        void addCommand(boost::shared_ptr<Command> cmd);
        void executeAll(DrawingManager* manager) const;
        
        const CommandMap& getCommands() const;
        
    private:
        CommandMap commands;
    };
}

