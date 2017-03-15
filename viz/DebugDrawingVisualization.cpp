#include "DebugDrawingVisualization.hpp"
#include <vizkit3d_debug_drawings/DrawingManager.h>
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
    //manager cannot be initalized before this point because the plugin is lazy initialzied.
    //I.e. getWidget() still returns nullptr when called from inside 
    //the ctor.
    if(!p->manager)
        p->manager.reset(new DrawingManager(getWidget()));
    return new osg::Group();
}

void DebugDrawingVisualization::updateMainNode(osg::Node* node)
{

}

void DebugDrawingVisualization::updateDataIntern(boost::shared_ptr<vizkit3dDebugDrawings::CommandBuffer> const& cmd)
{
    p->data = cmd;
    if(p->data)
    {
        p->manager->clearAllDrawings();
        p->data->executeAll(p->manager.get());
    }
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(DebugDrawingVisualization)

