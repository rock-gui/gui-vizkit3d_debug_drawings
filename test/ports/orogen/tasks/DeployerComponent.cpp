#include <rtt/Component.hpp>

#include <tasks/Task.hpp>

ORO_CREATE_COMPONENT_TYPE();
ORO_LIST_COMPONENT_TYPE( component::Task );

namespace orogen
{
    RTT::TaskContext* create_component__Task(std::string const& instance_name)
    {
        return new component::Task(instance_name);
    }
}
