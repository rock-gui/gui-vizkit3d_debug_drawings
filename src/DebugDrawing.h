#pragma once

/**This is the main header that should be included to use debug drawings.
 * It defines all required macros */

#ifndef ENABLE_DEBUG_DRAWINGS

    #define DRAW_RING(...) (void)0
    #define DRAW_PRIMITIVE(...) (void)0
    #define DRAW_WIREFRAME_BOX(...) (void) 0
    #define REMOVE_DRAWING(...) (void) 0
    #define CLEAR_DRAWING(...) (void) 0
    #define DRAW_SPHERE(...) (void)0
    #define DRAW_POLYLINE(...) (void)0
    
    
    #define COMPLEX_DRAWING(...) (void)0
    
    
    
#else

#include <string>
#include "DrawingManager.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>
#include <vector>
#include <base/Eigen.hpp>

    /**Draws any osgviz object
     * @param prim Pointer to osgviz::Object 
     */
    void DRAW_PRIMITIVE(const std::string& drawingName, double posX, double posY, double posZ,
                        double rotW, double rotX, double rotY, double rotZ, osg::ref_ptr<osgviz::Object> prim)
    {
        prim->setPosition(posX, posY, posZ);
        prim->setOrientation(rotX, rotY, rotZ, rotW);
        vizkit3dDebugDrawings::DrawingManager::instance()->addPrimitive(drawingName, prim);
    }

    void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ,
                            double rotW, double rotX, double rotY, double rotZ, double xSize,
                            double ySize, double zSize)
    {
        osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
        auto prim = fac->createWireframeBox(xSize, ySize, zSize);
        DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
    }
    
    void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ,
                            double xSize, double ySize, double zSize)
    {
        DRAW_WIREFRAME_BOX(drawingName, posX, posY, posZ, 1, 0, 0, 0, xSize, ySize, zSize);
    }
    
    void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ)
    {
        DRAW_WIREFRAME_BOX(drawingName, posX, posY, posZ, 1, 1, 1);
    }
    
    void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                            double rotW, double rotX, double rotY, double rotZ, double xScale,
                            double yScale, double zScale)
    {
        osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
        auto prim = fac->createArrow();
        prim->setScale(xScale, yScale, zScale);
        DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
    }
    
    void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                    double xScale, double yScale, double zScale)
    {
        DRAW_ARROW(drawingName, posX, posY, posZ, 1, 0, 0, 0, xScale, yScale, zScale);
    }
    
    void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ)
    {
        DRAW_ARROW(drawingName, posX, posY, posZ, 1, 1, 1);
    }
    
    
    void DRAW_RING(const std::string& drawingName, double posX, double posY, double posZ,
                   double rotW, double rotX, double rotY, double rotZ, double radius,
                   double height, double thickness) 
    { 
        osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
        auto prim = fac->createRingNode(radius, height, thickness);
        DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
    }
    
    void DRAW_RING(const std::string& drawingName, double posX, double posY, double posZ,
                   double radius, double height, double thickness)
    {
        DRAW_RING(drawingName, posX, posY, posZ, 1, 0, 0, 0, radius, height, thickness);
    }
    
    void DRAW_SPHERE(const std::string& drawingName, double posX, double posY, double posZ,
                     double radius)
    {
        osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
        auto prim = fac->createSphereNode(0, 0, 0, radius);
        DRAW_PRIMITIVE(drawingName, posX, posY, posZ, 1, 0, 0, 0, prim);
    }
    
    void DRAW_POLYLINE(const std::string& drawingName, double posX, double posY, double posZ,
                       const std::vector<base::Vector3d>& points)
    {
        osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
        std::vector<osg::Vec3> osgPoints;
        for(const base::Vector3d& p : points)
        {
            osgPoints.emplace_back(p.x(), p.y(), p.z());
        }
        auto prim = fac->createLinesNode(osg::Vec4(1, 1, 1, 1), osgPoints);
        DRAW_PRIMITIVE(drawingName, posX, posY, posZ, 1, 0, 0, 0, prim);
    }
    
    /** Removes the drawing.
     * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
     * @note If you want to animate something, use CLEAR_DRAWING instead.*/
    void REMOVE_DRAWING(const std::string& drawingName)
    {
        vizkit3dDebugDrawings::DrawingManager::instance()->removeDrawing(drawingName);
    }
    
    /** Removes the content from a drawing but keeps the drawing itself.
     * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
     * Use this if you want to animate movements.*/
    void CLEAR_DRAWING(const std::string& drawingName)
    {
        vizkit3dDebugDrawings::DrawingManager::instance()->clearDrawing(drawingName);
    }
    
    /**Use this if debug drawings need additional code that is only required for the drawing */
    #define COMPLEX_DRAWING(...) do { __VA_ARGS__; } while (0)
    

#endif


