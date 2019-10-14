#pragma once
#include <memory>
#include <mutex>
#include "ICommandDispatcher.hpp"
#include <vector>
#include <string>

namespace RTT
{
    class TaskContext;
}

namespace vizkit3d
{
    class Vizkit3DWidget;
}

namespace vizkit3dDebugDrawings
{
    /** a thread local singleton that dispatches drawing commands to different
     *  targets. */
    class CommandDispatcherFactory
    {
    public:
      
#ifdef USE_PORTS
        /**Is thread safe
         * @p drawingChannels names of all drawingGroups that should be routed to this task*/
        static void createPortDispatcher(RTT::TaskContext* taskContext, const std::vector<std::string>& drawingChannels);
#endif
        
        /**Is thread safe */
        static void createStandaloneDispatcher();
        
        /**Is thread safe */
        static void createWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget);
        
        /** @return true if an instance has been created.
         * Is thread safe*/
        static bool instanceExists();
        
        
        /** @return  instance of the CommandDispatcher.
         *  @throws std::runtime_error if no dispatcher has been created prior 
         *                             to this call
         * Is thread safe*/
        static std::shared_ptr<ICommandDispatcher> getInstance();

    private:
        static std::shared_ptr<ICommandDispatcher> dispatcher;
        static std::mutex createMutex;
    };
}
