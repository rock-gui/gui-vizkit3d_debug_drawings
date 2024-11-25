#include "Task.hpp"

#include <vizkit3d_debug_drawings/DebugDrawing.hpp>

using namespace component;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::~Task()
{
}

bool Task::configureHook()
{
    std::vector<std::string> channels = V3DD::GET_DECLARED_CHANNELS();
    std::vector<std::string> channels_filtered;
    for(const std::string& channel : channels)
    {
        //check if it contains ugv
        if(channel.find("area_explorer") != std::string::npos)
        {
            channels_filtered.push_back(channel);
        }
    }
    V3DD::CONFIGURE_DEBUG_DRAWINGS_USE_PORT(this, channels_filtered);

    V3DD::FLUSH_DRAWINGS();
    
    if (! TaskBase::configureHook())
        return false;
    return true;
}

bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    V3DD::FLUSH_DRAWINGS();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}

