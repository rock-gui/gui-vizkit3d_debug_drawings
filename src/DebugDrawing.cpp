#define ENABLE_DEBUG_DRAWINGS //to get the right version of the header
#include "commands/primitives/DrawSphereCommand.h"
#include "commands/primitives/DrawTextCommand.h"
#include "commands/primitives/DrawRingCommand.h"
#include "commands/primitives/DrawWireframeBoxCommand.h"
#include "CommandDispatcher.h"
#include <vizkit3d/Vizkit3DWidget.hpp>

using namespace vizkit3dDebugDrawings;


void DRAW_WIREFRAME_BOX(const std::string& drawingName, const base::Vector3d& position,
                        const base::Quaterniond& orientation, const base::Vector3d& size,
                        const base::Vector4d& colorRGBA)
{
    DrawWireframeBoxCommand cmd(drawingName, position, orientation, size, colorRGBA);
    CommandDispatcher::threadLocalInstance()->dispatch(cmd);        
}

void DRAW_WIREFRAME_BOX(const std::string& drawingName, const base::Vector3d& position,
                        const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_WIREFRAME_BOX(drawingName, position, base::Quaterniond::Identity(), size, colorRGBA);
}

void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                        double rotW, double rotX, double rotY, double rotZ, double xScale,
                double yScale, double zScale, const base::Vector4d& colorRGBA)
{
//     osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
//     const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
//     auto prim = fac->createArrow(color);
//     prim->setScale(xScale, yScale, zScale);
//     DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
}

void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                double xScale, double yScale, double zScale, const base::Vector4d& colorRGBA)
{
//     DRAW_ARROW(drawingName, posX, posY, posZ, 1, 0, 0, 0, xScale, yScale, zScale, colorRGBA);
}

void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ, const base::Vector4d& colorRGBA)
{
//     DRAW_ARROW(drawingName, posX, posY, posZ, 1, 1, 1, colorRGBA);
}

void DRAW_RING(const std::string& drawingName, const base::Vector3d& position,
               const base::Quaterniond& orientation, double radius,
               double height, double thickness, const base::Vector4d& colorRGBA) 
{ 
    DrawRingCommand cmd(drawingName, position, orientation, height, thickness, radius,
                        colorRGBA);
    CommandDispatcher::threadLocalInstance()->dispatch(cmd);    
}

void DRAW_RING(const std::string& drawingName, const base::Vector3d& position,
               double radius, double height, double thickness, const base::Vector4d& colorRGBA)
{
    DRAW_RING(drawingName, position, base::Quaterniond::Identity(), radius,
              height, thickness, colorRGBA);
}

void DRAW_SPHERE(const std::string& drawingName, const base::Vector3d& position,
                 double radius, const base::Vector4d& colorRGBA)
{
    DrawSphereCommand cmd(drawingName, position, radius, colorRGBA);
    CommandDispatcher::threadLocalInstance()->dispatch(cmd);
}

void DRAW_SPHERE(const std::string& drawingName, double posX, double posY, double posZ,
                 double radius, const base::Vector4d& colorRGBA)
{
    DRAW_SPHERE(drawingName, base::Vector3d(posX, posY, posZ), radius, colorRGBA);
}

void DRAW_POLYLINE(const std::string& drawingName, double posX, double posY, double posZ,
                   const std::vector<base::Vector3d>& points, const base::Vector4d& colorRGBA)
{
//     osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
//     std::vector<osg::Vec3> osgPoints;
//     for(const base::Vector3d& p : points)
//     {
//         osgPoints.emplace_back(p.x(), p.y(), p.z());
//     }
//     const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
//     auto prim = fac->createLinesNode(color, osgPoints);
//     DRAW_PRIMITIVE(drawingName, posX, posY, posZ, 1, 0, 0, 0, prim);
}

void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& position,
               const base::Quaterniond& orientation, const std::string& text,
               double fontSize, const base::Vector4d& colorRGBA)
{
    
    DrawTextCommand cmd(drawingName, position, orientation, text, fontSize, colorRGBA);
    CommandDispatcher::threadLocalInstance()->dispatch(cmd);
}

void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& position,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, position, base::Quaterniond::Identity(), text, fontSize, colorRGBA);
}

void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, base::Vector3d(posX, posY, posZ), base::Quaterniond(rotW, rotX, rotY, rotZ),
                                          text, fontSize, colorRGBA);    
}

void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, base::Vector3d(posX, posY, posZ), base::Quaterniond::Identity(),
                                          text, fontSize, colorRGBA);     
}

void DRAW_LINE(const std::string& drawingName, const base::Vector3d& from, const base::Vector3d& to,
               const base::Vector4d& colorRGBA)
{
//     osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
//     std::vector<osg::Vec3> osgPoints;
//     osgPoints.emplace_back(from.x(), from.y(), from.z());
//     osgPoints.emplace_back(to.x(), to.y(), to.z());
//     
//     const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
//     auto prim = fac->createLinesNode(color, osgPoints);
//     DRAW_PRIMITIVE(drawingName, 0, 0, 0, 1, 0, 0, 0, prim);
}


/** Removes the drawing.
 * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
 * @note If you want to animate something, use CLEAR_DRAWING instead.*/
void REMOVE_DRAWING(const std::string& drawingName)
{
//     vizkit3dDebugDrawings::DrawingManager::instance()->removeDrawing(drawingName);
}

/** Removes the content from a drawing but keeps the drawing itself.
 * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
 * Use this if you want to animate movements.*/
void CLEAR_DRAWING(const std::string& drawingName)
{
//     vizkit3dDebugDrawings::DrawingManager::instance()->clearDrawing(drawingName);
}

void CONFIGURE_DEBUG_DRAWINGS_STANDALONE()
{
    CommandDispatcher::threadLocalInstance()->configureStandalone();
}

void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget * widget)
{
    CommandDispatcher::threadLocalInstance()->configureUseWidget(widget);
}

void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::OutputPort<Command>* port)
{
    CommandDispatcher::threadLocalInstance()->configurePort(port);
}
