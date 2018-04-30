#include "DrawWireframeBoxCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>

namespace vizkit3dDebugDrawings
{
    
osg::ref_ptr<osgviz::Object> DrawWireframeBoxCommand::createPrimitive() const
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createWireframeBox(size.x(), size.y(), size.z(), color);
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
    
}

DrawWireframeBoxCommand::DrawWireframeBoxCommand(const std::string& drawingGroupName,
                                                 const Eigen::Vector3d& position,
                                                 const Eigen::Quaterniond& orientation,
                                                 const Eigen::Vector3d& size,
                                                 const Eigen::Vector4d& colorRGBA):
        DrawCommand(drawingGroupName), position(position), orientation(orientation),
        size(size), colorRGBA(colorRGBA)
{}

DrawWireframeBoxCommand::DrawWireframeBoxCommand(): DrawCommand("default")
{}

DrawWireframeBoxCommand* DrawWireframeBoxCommand::clone() const
{
    return new DrawWireframeBoxCommand(*this);
}


}


