#pragma once
#include <rtt/OutputPort.hpp>
#include <boost/shared_ptr.hpp>

namespace vizkit3d
{
    class Vizkit3DWidget;
}

namespace vizkit3dDebugDrawings
{
    class DrawingManager;
    class Command;
    class CommandBuffer;
    
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
         *  The command is dispatched or buffered depending on the configuration.
         *  The buffer is a ring buffer of size 100000*/
        void dispatch(const Command& cmd);
        
        /**Configures the dispatcher. Until configured, all commands are buffered
         * @throw std::runtime_error if already configured*/
        void configurePort(RTT::OutputPort<boost::shared_ptr<CommandBuffer>>* port);
        void configureStandalone();
        void configureUseWidget(vizkit3d::Vizkit3DWidget* widget);
        
        bool isConfigured() const;
        
        /** Returns the widget that is used for drawing.
         *  @throw std::runtime_error if no widget is configured*/
        vizkit3d::Vizkit3DWidget* getWidget();
        
    private:
        
        //only threadLocalInstance() may create instances
        CommandDispatcher();
        ~CommandDispatcher();
        void checkAndSetConfigured();
        void dispatchBufferedCommands();
        
        DrawingManager* getDrawingManager();
        
        //pimpl to hide as much of the implementation as possible to reduce compile time
        struct Impl;
        Impl* p;
    };
}