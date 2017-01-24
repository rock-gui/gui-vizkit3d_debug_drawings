#pragma once

/**This is the main header that should be included to use debug drawings.
 * It defines all required macros */

//#ifdef NDEBUG
//    #define DRAW_RING(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, radius, height, thickness) (void)0
//#else
#include "DrawingManager.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>
    
    #define DRAW_RING(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, radius, height, thickness) \
    do \
    { \
        osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory"); \
        auto prim = fac->createRingNode(radius, height, thickness); \
        prim->setPosition(posX, posY, posZ); \
        prim->setOrientation(rotX, rotY, rotZ, rotW); \
        vizkit3dDebugDrawings::DrawingManager::instance()->addPrimitive(drawingName, prim); \
    } while(false)

//#endif


