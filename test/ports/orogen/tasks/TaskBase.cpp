/* Generated from orogen/lib/orogen/templates/tasks/TAskBase.cpp */

#include "orogen/tasks/TaskBase.hpp"

using namespace component;



#ifdef HAS_GETTID
#include <sys/syscall.h>
#endif


TaskBase::TaskBase(std::string const& name)
    : ::RTT::TaskContext(name, TaskCore::PreOperational)
    , ___orogen_getTID("__orogen_getTID", &TaskBase::__orogen_getTID, this, RTT::OwnThread)
    , _state("state") {
    setupComponentInterface();
}

TaskBase::TaskBase(std::string const& name, RTT::ExecutionEngine* engine)
    : ::RTT::TaskContext(name, TaskCore::PreOperational)
    , ___orogen_getTID("__orogen_getTID", &TaskBase::__orogen_getTID, this, RTT::OwnThread)
    , _state("state"){
    setupComponentInterface();
}

TaskBase::~TaskBase()
{
}

void TaskBase::setupComponentInterface()
{
    provides()->addOperation( ___orogen_getTID)
        .doc("returns the PID for this task");
    _state.keepLastWrittenValue(false);
    _state.keepNextWrittenValue(true);
    ports()->addPort(_state);

    
    _state.keepLastWrittenValue(true);
    _state.write(getTaskState());
    
}

boost::int32_t TaskBase::__orogen_getTID()
{
    #ifdef HAS_GETTID
return syscall(SYS_gettid);
#else
return 0;
#endif
}
::std::string TaskBase::getModelName()
{
    return "component::Task";
}

void TaskBase::error()
{ return error(RUNTIME_ERROR); }
void TaskBase::exception()
{ return exception(EXCEPTION); }
void TaskBase::fatal()
{ return fatal(FATAL_ERROR); }

void TaskBase::report(States state)
{
    _state.write(state);
}
void TaskBase::state(States state)
{
    _state.write(state);
}
void TaskBase::error(States state)
{
    _state.write(state);
    TaskContext::error();
}
void TaskBase::exception(States state)
{
    _state.write(state);
    TaskContext::exception();
}
void TaskBase::fatal(States state)
{
    _state.write(state);
    TaskContext::fatal();
}
TaskBase::States TaskBase::state() const
{
    return static_cast<TaskBase::States>(_state.getLastWrittenValue());
}

#ifdef RTT_HAS_STATE_CHANGE_HOOK
bool TaskBase::start()
{
    
    return RTT::TaskContext::start();
}

typedef RTT::base::TaskCore::TaskState TaskState;
typedef TaskBase::States OroGenStates;
static bool isRuntimeState(OroGenStates state) {
    return false;
}
static bool isRuntimeErrorState(OroGenStates state) {
    
    
    return false;
    
}
static bool isExceptionState(OroGenStates state) {
    
    
    return false;
    
}
static bool isFatalErrorState(OroGenStates state) {
    
    
    return false;
    
}
void TaskBase::setTaskState(TaskState state) {
    RTT::TaskContext::setTaskState(state);

    States lastPublishedState = this->state();
    switch(state) {
        case TaskState::Running:
            if (isRuntimeState(lastPublishedState)) {
                return;
            }
            break;
        case TaskState::RunTimeError:
            if (isRuntimeErrorState(lastPublishedState)) {
                return;
            }
            break;
        case TaskState::Exception:
            if (isExceptionState(lastPublishedState)) {
                return;
            }
            break;
        case TaskState::FatalError:
            if (isFatalErrorState(lastPublishedState)) {
                return;
            }
            break;
        default:
            break;
    }
    _state.write(state);
}

#else
struct StateExporter
{
    RTT::TaskContext const& task;
    RTT::OutputPort<boost::int32_t>&   port;

    StateExporter(RTT::TaskContext const& task, RTT::OutputPort<int>& port)
        : task(task), port(port) {}
    ~StateExporter()
    {
        port.write(task.getTaskState());
    }
};

bool TaskBase::start()
{
    StateExporter exporter(*this, _state);
    bool started = RTT::TaskContext::start();
    if (!started)
        return false;

    
    _map.clear();
    
    _pose_samples.clear();
    
    _planner_state.clear();
    
    _area.clear();
    
    return true;
}

bool TaskBase::configure()
{
    StateExporter exporter(*this, _state);
    return RTT::TaskContext::configure();
}
bool TaskBase::recover()
{
    StateExporter exporter(*this, _state);
    return RTT::TaskContext::recover();
}
bool TaskBase::stop()
{
    StateExporter exporter(*this, _state);
    return RTT::TaskContext::stop();
}
bool TaskBase::cleanup()
{
    StateExporter exporter(*this, _state);
    return RTT::TaskContext::cleanup();
}
#endif

bool TaskBase::configureHook()
{
    
    if (! ::RTT::TaskContext::configureHook())
        return false;
    
    
    return true;
    
}
bool TaskBase::startHook()
{
    
    if (! ::RTT::TaskContext::startHook())
        return false;
    
    
    return true;
    
}

