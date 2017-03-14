#include <boost/test/unit_test.hpp>
#define private public //HACK to compare members of DrawSphereCommand
#include <vizkit3d_debug_drawings/commands/primitives/DrawSphereCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawArrowCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawCylinderCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawPolyLineCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawRingCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawTextCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawWireframeBoxCommand.h>
#include <vizkit3d_debug_drawings/commands/ClearDrawingCommand.h>
#include <vizkit3d_debug_drawings/commands/RemoveDrawingCommand.h>
#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <rtt/OutputPort.hpp>
#include <rtt/InputPort.hpp>


using namespace vizkit3dDebugDrawings;

BOOST_AUTO_TEST_CASE(port_test)
{
    RTT::OutputPort<boost::shared_ptr<Command>> port;
    RTT::InputPort<boost::shared_ptr<Command>> input;
    
    port.connectTo(input);
    
    CONFIGURE_DEBUG_DRAWINGS_USE_PORT(&port);
    
    DRAW_CYLINDER("cylinder", base::Vector3d(3, 3, 2), base::Vector3d(1,1,1),
                  vizkit3dDebugDrawings::Color::android_green);
    
    input.readNewest();
}