#define ENABLE_DEBUG_DRAWINGS //to get the right version of the header
#include "DebugDrawing.h"

void DRAW_PRIMITIVE(const std::string& drawingName, double posX, double posY, double posZ,
                    double rotW, double rotX, double rotY, double rotZ, osg::ref_ptr<osgviz::Object> prim)
{
    prim->setPosition(posX, posY, posZ);
    prim->setOrientation(rotX, rotY, rotZ, rotW);
    vizkit3dDebugDrawings::DrawingManager::instance()->addPrimitive(drawingName, prim);
}

void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ,
                        double rotW, double rotX, double rotY, double rotZ, double xSize,
                        double ySize, double zSize, const base::Vector4d& colorRGBA)
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createWireframeBox(xSize, ySize, zSize, color);
    DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
}

void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ,
                        double xSize, double ySize, double zSize, const base::Vector4d& colorRGBA)
{
    DRAW_WIREFRAME_BOX(drawingName, posX, posY, posZ, 1, 0, 0, 0, xSize, ySize, zSize, colorRGBA);
}

void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY,
                        double posZ, const base::Vector4d& colorRGBA)
{
    DRAW_WIREFRAME_BOX(drawingName, posX, posY, posZ, 1, 1, 1, colorRGBA);
}

void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                        double rotW, double rotX, double rotY, double rotZ, double xScale,
                double yScale, double zScale, const base::Vector4d& colorRGBA)
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createArrow(color);
    prim->setScale(xScale, yScale, zScale);
    DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
}

void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                double xScale, double yScale, double zScale, const base::Vector4d& colorRGBA)
{
    DRAW_ARROW(drawingName, posX, posY, posZ, 1, 0, 0, 0, xScale, yScale, zScale, colorRGBA);
}

        void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ, const base::Vector4d& colorRGBA)
{
    DRAW_ARROW(drawingName, posX, posY, posZ, 1, 1, 1, colorRGBA);
}


void DRAW_RING(const std::string& drawingName, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ, double radius,
               double height, double thickness, const base::Vector4d& colorRGBA) 
{ 
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createRingNode(radius, height, thickness, color);
    
    DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
}

void DRAW_RING(const std::string& drawingName, double posX, double posY, double posZ,
               double radius, double height, double thickness, const base::Vector4d& colorRGBA)
{
    DRAW_RING(drawingName, posX, posY, posZ, 1, 0, 0, 0, radius, height, thickness, colorRGBA);
}

void DRAW_SPHERE(const std::string& drawingName, double posX, double posY, double posZ,
                 double radius, const base::Vector4d& colorRGBA)
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createSphereNode(0, 0, 0, radius, color);
    DRAW_PRIMITIVE(drawingName, posX, posY, posZ, 1, 0, 0, 0, prim);    
}

void DRAW_SPHERE(const std::string& drawingName, base::Vector3d& position,
                 double radius, const base::Vector4d& colorRGBA)
{
    DRAW_SPHERE(drawingName, position.x(), position.y(), position.z(), radius, colorRGBA);
}

void DRAW_POLYLINE(const std::string& drawingName, double posX, double posY, double posZ,
                   const std::vector<base::Vector3d>& points, const base::Vector4d& colorRGBA)
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    std::vector<osg::Vec3> osgPoints;
    for(const base::Vector3d& p : points)
    {
        osgPoints.emplace_back(p.x(), p.y(), p.z());
    }
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createLinesNode(color, osgPoints);
    DRAW_PRIMITIVE(drawingName, posX, posY, posZ, 1, 0, 0, 0, prim);
}

void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createTextNode(text, fontSize, color);
    DRAW_PRIMITIVE(drawingName, posX, posY, posZ, rotW, rotX, rotY, rotZ, prim);
}

void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, posX, posY, posZ, 1, 0, 0, 0, text, fontSize, colorRGBA);
}

void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& pos,
               const base::Quaterniond& rot, const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, pos.x(), pos.y(), pos.z(), rot.w(), rot.x(), rot.y(),
              rot.z(), text, fontSize, colorRGBA);
}

void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& pos,
            const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, pos, base::Quaterniond::Identity(), text, fontSize, colorRGBA);
}

void DRAW_LINE(const std::string& drawingName, const base::Vector3d& from, const base::Vector3d& to,
               const base::Vector4d& colorRGBA)
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    std::vector<osg::Vec3> osgPoints;
    osgPoints.emplace_back(from.x(), from.y(), from.z());
    osgPoints.emplace_back(to.x(), to.y(), to.z());
    
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createLinesNode(color, osgPoints);
    DRAW_PRIMITIVE(drawingName, 0, 0, 0, 1, 0, 0, 0, prim);
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