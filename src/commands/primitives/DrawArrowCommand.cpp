#include "DrawArrowCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>
namespace vizkit3dDebugDrawings
{
    
osg::ref_ptr< osgviz::Object > DrawArrowCommand::createPrimitive() const
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createArrow(color);
    prim->setScale(scale.x(), scale.y(), scale.z());
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
}

DrawArrowCommand::DrawArrowCommand(const std::string& drawingName, const base::Vector3d& position,
                                   const base::Quaterniond& orientation, const base::Vector3d& scale,
                                   const base::Vector4d& colorRGBA) :
        DrawCommand(drawingName), position(position), orientation(orientation), 
        scale(scale), colorRGBA(colorRGBA)
{}
    
DrawArrowCommand::DrawArrowCommand(): DrawCommand("default")
{}

}