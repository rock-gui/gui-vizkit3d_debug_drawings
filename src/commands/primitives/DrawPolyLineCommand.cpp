#include "DrawPolyLineCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>

namespace vizkit3dDebugDrawings
{

std::vector< Eigen::Vector3d >& DrawPolyLineCommand::getPoints()
{
    return points;
}


osg::ref_ptr< osgviz::Object > DrawPolyLineCommand::createPrimitive() const
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    std::vector<osg::Vec3> osgPoints;
    for(const Eigen::Vector3d& p : points)
    {
        osgPoints.emplace_back(p.x(), p.y(), p.z());
    }
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createLinesNode(color, osgPoints);
    prim->setPosition(position.x(), position.y(), position.z());
    return prim;
}

DrawPolyLineCommand::DrawPolyLineCommand(const std::string& drawingGroupName,
                                         const Eigen::Vector3d& position,
                                         const Eigen::Vector4d& colorRGBA):
        DrawCommand(drawingGroupName), position(position), colorRGBA(colorRGBA)
{}
 
DrawPolyLineCommand::DrawPolyLineCommand(): DrawCommand("default")
{

}

DrawPolyLineCommand* DrawPolyLineCommand::clone() const
{
    return new DrawPolyLineCommand(*this);
}

}
