#include "DrawTextCommand.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>


namespace vizkit3dDebugDrawings
{
DrawTextCommand::DrawTextCommand(const std::string& drawingName,
                                 const base::Vector3d& position,
                                 const base::Quaterniond& orientation,
                                 const std::string& text, double fontSize,
                                 const base::Vector4d& colorRGBA): 
         DrawCommand(drawingName), position(position), orientation(orientation),
         text(text), fontSize(fontSize), colorRGBA(colorRGBA)
{}

osg::ref_ptr< osgviz::Object > DrawTextCommand::createPrimitive() const
{
    osgviz::PrimitivesFactory* fac = osgviz::OsgViz::getInstance()->getModuleInstance<osgviz::PrimitivesFactory>("PrimitivesFactory");
    const osg::Vec4 color(colorRGBA[0], colorRGBA[1], colorRGBA[2], colorRGBA[3]);
    auto prim = fac->createTextNode(text, fontSize, color);
    prim->setPosition(position.x(), position.y(), position.z());
    prim->setOrientation(orientation.x(), orientation.y(), orientation.z(), orientation.w());
    return prim;
}


DrawTextCommand::DrawTextCommand(): DrawCommand("default")
{

}

DrawTextCommand* DrawTextCommand::clone() const
{
    return new DrawTextCommand(*this);
}

}

