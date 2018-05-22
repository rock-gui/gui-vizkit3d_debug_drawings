#include "DrawRingCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>


namespace vizkit3dDebugDrawings
{
    
DrawRingCommand::DrawRingCommand(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                                 const Eigen::Quaterniond& orientation, double height,
                                 double thickness, double radius, const Eigen::Vector4d& colorRGBA):
        DrawCommand(drawingGroupName), position(position), orientation(orientation),
        height(height), thickness(thickness), radius(radius), colorRGBA(colorRGBA)
{}

DrawRingCommand::DrawRingCommand(): DrawCommand("default")
{}

osg::ref_ptr< osgviz::Object > DrawRingCommand::createPrimitive() const
{
    auto const & fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createRingNode(radius, height, thickness, color);
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
}

DrawRingCommand* DrawRingCommand::clone() const
{
    return new DrawRingCommand(*this);
}

}

