#include "DebugDrawingVisualization.hpp"
#include <vizkit3d_debug_drawings/DrawingManager.hpp>
#include <memory>

using namespace vizkit3d;
using namespace vizkit3dDebugDrawings;

struct DebugDrawingVisualization::Data {    
    std::unique_ptr<DrawingManager> manager; //pointer because lazy init
    boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer> data;
};


DebugDrawingVisualization::DebugDrawingVisualization()
    : p(new Data)
{
}

DebugDrawingVisualization::~DebugDrawingVisualization()
{
    delete p;
}

osg::ref_ptr<osg::Node> DebugDrawingVisualization::createMainNode()
{
    return new osg::Group();
}

void DebugDrawingVisualization::createManager()
{
    if(!p->manager)
        p->manager.reset(new DrawingManager(getWidget()));
}


void DebugDrawingVisualization::updateMainNode(osg::Node* node)
{

}

void DebugDrawingVisualization::updateDataIntern(boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer> const& cmd)
{
    createManager();
    p->data = cmd;
    if(p->data)
    {
        //The drawing manager handles all the threading issues.
        p->manager->clearAllDrawings();
        p->data->executeAll(p->manager.get());
    }
}

namespace vizkit3d {
VizkitQtPluginImpl(DebugDrawingVisualization)
}
