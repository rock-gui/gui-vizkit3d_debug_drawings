#pragma once
#include <memory>
#include <mutex>
#include "ICommandDispatcher.hpp"

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
        static void createPortDispatcher(RTT::TaskContext* taskContext);
#endif
        static void createStandaloneDispatcher();
        static void createWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget);
        
        /** @return true if an instance has been created */
        static bool instanceExists();
        
        
        /** @return a thread_local instance of the CommandDispatcher.
         *  @throws std::runtime_error if no dispatcher has been created prior 
         *                             to this call*/
        static std::shared_ptr<ICommandDispatcher> getThreadLocalInstance();

    private:
        static thread_local std::shared_ptr<ICommandDispatcher> dispatcher;
    };
}