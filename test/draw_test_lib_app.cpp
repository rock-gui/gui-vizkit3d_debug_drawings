#include <vizkit3d_debug_drawings/DebugDrawing.hpp>
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>

void library_entry();

int main()
{
    // for lib_enabled_app_enabled, a vizkit window with a drawing should appear.
    // for all other cases, only an empty vizkit window should pop up

    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread;
    thread.start();
    V3DD::CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(thread.getWidget());


    library_entry();
    return 0;
}

