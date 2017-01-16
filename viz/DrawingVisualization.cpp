#include <iostream>
#include "DrawingVisualization.hpp"

using namespace vizkit3d;

struct DrawingVisualization::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    vizkti3dDebugDrawings::Drawing data;
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
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void DrawingVisualization::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void DrawingVisualization::updateDataIntern(vizkti3dDebugDrawings::Drawing const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(DrawingVisualization)

