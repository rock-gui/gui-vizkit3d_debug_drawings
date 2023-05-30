#include <iostream>
#include "DrawingVisualization.hpp"

using namespace vizkit3d;

struct DrawingVisualization::Data {
    vizkit3dDebugDrawings::Drawing data;
};


DrawingVisualization::DrawingVisualization()
    : p(new Data)
{
}

DrawingVisualization::~DrawingVisualization()
{
    delete p;
}

osg::ref_ptr<osg::Node> DrawingVisualization::createMainNode()
{
    return new osg::Group();
}

void DrawingVisualization::updateMainNode(osg::Node* node)
{
    osg::Group *main = node->asGroup();
    main->removeChildren(0, main->getNumChildren());
    
    for(const osg::ref_ptr<osgviz::Object>& prim : p->data.getPrimitives())
    {
        main->addChild(prim.get());
    }
}

void DrawingVisualization::updateDataIntern(vizkit3dDebugDrawings::Drawing const& value)
{
    p->data = value;
    const QString pluginName = QString("Debug Drawing: ") + QString(p->data.getName().c_str());
    if(getPluginName() != pluginName)
    {
        setPluginName(pluginName);
    }
}

namespace vizkit3d {
VizkitQtPluginImpl(DrawingVisualization)
}
