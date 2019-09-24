#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include "draw.h"


int main()
{
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread;
    thread.start();
    CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(thread.getWidget());
    
    
    draw();   
    return 0;
}
