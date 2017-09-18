#include "DrawSphereCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>

namespace vizkit3dDebugDrawings
{
    
DrawSphereCommand::DrawSphereCommand(): DrawCommand("default")
{

}

    
    
DrawSphereCommand::DrawSphereCommand(const std::string& drawingGroupName,
                                                            const base::Vector3d& position,
                                                            double radius,
                                                            const base::Vector4d& colorRGBA) :
        DrawCommand(drawingGroupName), position(position), radius(radius), colorRGBA(colorRGBA)
{}

osg::ref_ptr<osgviz::Object> DrawSphereCommand::createPrimitive() const
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createSphereNode(0, 0, 0, radius, color);
    prim->setPosition(position.x(), position.y(), position.z());
    return prim;
}

DrawSphereCommand* DrawSphereCommand::clone() const
{
    return new DrawSphereCommand(*this);
}

}

