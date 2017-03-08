// #include "DebugDrawingVisualization.hpp"
// 
// using namespace vizkit3d;
// 
// struct DebugDrawingVisualization::Data {
// 
// };
// 
// 
// DebugDrawingVisualization::DebugDrawingVisualization()
//     : p(new Data)
// {
// }
// 
// DebugDrawingVisualization::~DebugDrawingVisualization()
// {
//     delete p;
// }
// 
// osg::ref_ptr<osg::Node> DebugDrawingVisualization::createMainNode()
// {
//     return new osg::Group();
// }
// 
// void DebugDrawingVisualization::updateMainNode(osg::Node* node)
// {
// //     osg::Group *main = node->asGroup();
// //     main->removeChildren(0, main->getNumChildren());
// //     
// //     for(const osg::ref_ptr<osgviz::Object>& prim : p->data.getPrimitives())
// //     {
// //         main->addChild(prim.get());
// //     }
// }
// 
// void DebugDrawingVisualization::updateDataIntern(vizkit3dDebugDrawings::Command const& value)
// {
// //     p->data = value;
// }
// 
// //Macro that makes this plugin loadable in ruby, this is optional.
// VizkitQtPlugin(DebugDrawingVisualization)
// 
