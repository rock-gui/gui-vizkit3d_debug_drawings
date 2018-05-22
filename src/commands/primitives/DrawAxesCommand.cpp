#include "DrawAxesCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>

vizkit3dDebugDrawings::DrawAxesCommand* vizkit3dDebugDrawings::DrawAxesCommand::clone() const
{
    return new DrawAxesCommand(*this);
}


osg::ref_ptr< osgviz::Object > vizkit3dDebugDrawings::DrawAxesCommand::createPrimitive() const
{
    auto const & fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    auto prim = fac->createAxes();
    prim->setScale(scale.x(), scale.y(), scale.z());
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
}

vizkit3dDebugDrawings::DrawAxesCommand::DrawAxesCommand(const std::string& drawingGroupName,
                                                        const Eigen::Vector3d& position,
                                                        const Eigen::Quaterniond& orientation,
                                                        const Eigen::Vector3d& scale)
    : DrawCommand(drawingGroupName), position(position), orientation(orientation), scale(scale)
{

}


vizkit3dDebugDrawings::DrawAxesCommand::DrawAxesCommand(): DrawCommand("default")
{

}

