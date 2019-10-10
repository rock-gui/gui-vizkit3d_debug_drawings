#include <vizkit3d_debug_drawings/DebugDrawing.hpp>
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include "draw.hpp"


int main()
{
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread;
    thread.start();
    V3DD::CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(thread.getWidget());
    
    
    draw();   
    return 0;
}
