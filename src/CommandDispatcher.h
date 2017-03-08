#pragma once
#include <rtt/OutputPort.hpp>
#include "commands/Command.h"

namespace vizkit3d
{
    class Vizkit3DWidget;
}

namespace vizkit3dDebugDrawings
{
    class DrawingManager;
    
    /** Dispatches drawing commands depending on a given configuration.
     *  All commands are buffered until a configuration is set.*/
    class CommandDispatcher
    {
    public:
        
        /** @return a thread_local instance of the CommandDispatcher
         *  @warning Do ***not*** delete the instance pointer. It will be 
         *           deleted automatically when the thread ends.*/
        static CommandDispatcher* threadLocalInstance();
        
        /** Dispatch the given drawing command.
         *  The command is dispatched or buffered depending on the configuration*/
        void dispatch(const Command& cmd);
        
        /**Configures the dispatcher. Until configured, all commands are buffered
         * @throw std::runtime_error if already configured*/
        void configurePort(RTT::OutputPort<Command>* port);
        void configureStandalone();
        void configureUseWidget(vizkit3d::Vizkit3DWidget* widget);
        
    private:
        
        //only threadLocalInstance() may create instances
        CommandDispatcher();
        ~CommandDispatcher();
        void checkAndSetConfigured();
        
        DrawingManager* getDrawingManager();
        
        //pimpl to hide as much of the implementation as possible to reduce compile time
        struct Impl;
        Impl* p;
    };
}