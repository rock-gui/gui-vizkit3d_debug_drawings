#include "DrawCylinderCommand.hpp"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>

namespace vizkit3dDebugDrawings
{
    
osg::ref_ptr< osgviz::Object > DrawCylinderCommand::createPrimitive() const
{
    auto const & fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createShape(osgviz::PrimitivesFactory::CYLINDER, size.x(), size.y(), size.z());
    prim->setColor(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
}

DrawCylinderCommand::DrawCylinderCommand(const std::string& drawingChannel,
                                         const Eigen::Vector3d& position,
                                         const Eigen::Quaterniond& orientation,
                                         const Eigen::Vector3d& size,
                                         const Eigen::Vector4d& colorRGBA):
        DrawCommand(drawingChannel), position(position), orientation(orientation),
        size(size), colorRGBA(colorRGBA)
{}

DrawCylinderCommand::DrawCylinderCommand(): DrawCommand("default")
{}

DrawCylinderCommand* DrawCylinderCommand::clone() const
{
    return new DrawCylinderCommand(*this);
}

}

