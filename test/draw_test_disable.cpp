#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include "draw.h"


int main()
{
    //NOTE an empty vizkit window should pop up
    
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread;
    thread.start();
    V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(thread.getWidget());
    
    
    draw();   
    return 0;
}

