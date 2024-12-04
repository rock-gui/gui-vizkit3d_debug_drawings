/* Generated from orogen/lib/orogen/templates/tasks/TaskBase.hpp */

#ifndef COMPONENT_TASK_TASK_BASE_HPP
#define COMPONENT_TASK_TASK_BASE_HPP

#include <string>
#include <boost/cstdint.hpp>
#include <rtt/TaskContext.hpp>

#include <rtt/Operation.hpp>
#include <rtt/Port.hpp>
#include <component/TaskStates.hpp>

extern template class RTT::Property< double >;

extern template class RTT::Property< double >;

extern template class RTT::Property< double >;

extern template class RTT::Property< double >;
#include <boost/cstdint.hpp>
extern template class RTT::Property< bool >;
#include <boost/cstdint.hpp>
#include <string>
extern template class RTT::Property< ::std::string >;


#include </usr/include/boost/shared_ptr.hpp>
#include <vizkit3d_debug_drawings/commands/CommandBuffer.hpp>
extern template class RTT::OutputPort< ::boost::shared_ptr< ::vizkit3dDebugDrawings::CommandBuffer > >;
extern template class RTT::base::ChannelElement< ::boost::shared_ptr< ::vizkit3dDebugDrawings::CommandBuffer > >;

#include <boost/cstdint.hpp>
#include <boost/cstdint.hpp>
#include <string>




#include <atomic>
#include <fcntl.h>
#include <sys/time.h>
#include <thread>
namespace component{
    class Task;
    /** The oroGen-generated part of component::Task
     *
     * It is used by oroGen and its plugins to define the task interfaces and set
     * up the component. Never edit yourself, as its content would be
     * overwritten at the next code generation.
     */
    class TaskBase : public ::RTT::TaskContext
        
    {
    protected:
        // Common implementation of interface setup for both task constructors
        void setupComponentInterface();
        ::std::string getModelName();

        /* base implementation of the __orogen_getTID operation
         */
        virtual boost::int32_t __orogen_getTID();
        RTT::Operation< boost::int32_t() > ___orogen_getTID;
        RTT::OutputPort< boost::int32_t > _state;

    public:
        
        enum States
        {
            
                INIT = Task_INIT,
            
                PRE_OPERATIONAL = Task_PRE_OPERATIONAL,
            
                FATAL_ERROR = Task_FATAL_ERROR,
            
                EXCEPTION = Task_EXCEPTION,
            
                STOPPED = Task_STOPPED,
            
                RUNNING = Task_RUNNING,
            
                RUNTIME_ERROR = Task_RUNTIME_ERROR
        };
        

	TaskBase(std::string const& name);
	TaskBase(std::string const& name, RTT::ExecutionEngine* engine);
        ~TaskBase();

        bool start();

        
#ifdef RTT_HAS_STATE_CHANGE_HOOK
        void setTaskState(TaskState state);

        
#else
        // Reimplement TaskCore base methods to export the states to the outside
        // world
        bool configure();
        bool recover();
        bool stop();
        bool cleanup();
        
#endif
        

        
        void error();
        void fatal();
        void exception();

        void report(States state);
        void state(States state);
        void error(States state);
        void fatal(States state);
        void exception(States state);
        States state() const;
        

        bool configureHook();
        bool startHook();
    };

}


#endif

