#include <boost/test/unit_test.hpp>
#include <vizkit3dDebugDrawings/Dummy.hpp>

using namespace vizkit3dDebugDrawings;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    vizkit3dDebugDrawings::DummyClass dummy;
    dummy.welcome();
}
