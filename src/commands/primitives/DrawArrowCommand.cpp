#include "DrawArrowCommand.hpp"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>

namespace vizkit3dDebugDrawings
{
    
osg::ref_ptr< osgviz::Object > DrawArrowCommand::createPrimitive() const
{
    auto const & fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createArrow(color);
    prim->setScale(scale.x(), scale.y(), scale.z());
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
}

DrawArrowCommand::DrawArrowCommand(const std::string& drawingChannel, const Eigen::Vector3d& position,
                                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& scale,
                                   const Eigen::Vector4d& colorRGBA) :
        DrawCommand(drawingChannel), position(position), orientation(orientation), 
        scale(scale), colorRGBA(colorRGBA)
{}
    
DrawArrowCommand::DrawArrowCommand(): DrawCommand("default")
{}

DrawArrowCommand* DrawArrowCommand::clone() const
{
    return new DrawArrowCommand(*this);
}


}
