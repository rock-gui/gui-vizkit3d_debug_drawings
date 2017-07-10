#pragma once
#include <boost/shared_ptr.hpp>


namespace vizkit3d
{
    class Vizkit3DWidget;
}

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
    class DrawingManager;
    class Command;
    class CommandBuffer;
    
    /** Dispatches drawing commands depending on a given configuration.
     *  If the dispatcher is not configured, the commands will be stored in
     *  a ring buffer until configuration.  */
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
        
        /**Configures the dispatcher. 
         * There are three possible configurations:
         *  - use ports      : The Dispatcher will create a port for each drawing and send the commands
         *  - run standalone : A qt app will be started in a new thread and all commands will be displayed
         *  - existing widget: An existing widget is used to display all commands.
         * 
         * @throw std::runtime_error if already configured.
         * */
        void configurePort(RTT::TaskContext* taskContext);
        void configureStandalone();
        void configureUseWidget(vizkit3d::Vizkit3DWidget* widget);
        
        
        
        bool isConfigured() const;
        
        /** Returns the widget that is used for drawing.
         *  @throw std::runtime_error if no widget is configured*/
        vizkit3d::Vizkit3DWidget* getWidget();
        
    private:
        
        /**Creates and returns the port for the specified @p drawingName.
         * Just returns it, if it already exists*/
        void writePort(const std::string& drawingName, 
                       boost::shared_ptr<CommandBuffer> buffer);
        
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