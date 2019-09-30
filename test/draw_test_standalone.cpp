#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include "draw.h"


int main()
{
    V3DD_CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    draw();
    return 0;
}
