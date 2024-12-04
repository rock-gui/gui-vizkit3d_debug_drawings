#ifndef COMPONENT_TASK_TASK_HPP
#define COMPONENT_TASK_TASK_HPP

#include "../orogen/tasks/TaskBase.hpp"

namespace component
{
    class Task : public TaskBase
    {
    friend class TaskBase;
    public:

        Task(std::string const& name = "component::Task");
        ~Task();

        bool configureHook();
        bool startHook();
        void updateHook();
        void errorHook();
        void stopHook();
        void cleanupHook();
    };
}

#endif
