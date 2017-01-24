#include "DrawingManager.h"
#include "Drawing.h"
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include <unordered_map>
#include <vector>
#include <osgViz/Object.h>

namespace vizkit3dDebugDrawings
{
    struct DrawingManager::PImpl
    {
        /**Current drawings by name */
        std::unordered_map<std::string, Drawing> drawings;
        std::unordered_map<std::string, QObject*> plugins;
        /**Gui thread*/
        QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread;
    };
    
    DrawingManager::DrawingManager() : p(new PImpl())
    {
        p->thread.start();
    }
    
    DrawingManager* DrawingManager::instance()
    {
        static DrawingManager* d = new DrawingManager();
        return d;
    }
    
    vizkit3d::Vizkit3DWidget* DrawingManager::getVizkit3DWidget() const
    {
        return p->thread.getWidget();
    }
    
    void DrawingManager::addPrimitive(const std::string& drawingName, const osg::ref_ptr<osgviz::Object>& primitive)
    {
        if(drawingName.empty())
        {
            throw new std::runtime_error("drawingName is empty");
        }
        Drawing& d = p->drawings[drawingName];
        d.addPrimitive(primitive);
        d.setName(drawingName); //d might be a new Drawing
        
        if(p->plugins.find(drawingName) == p->plugins.end())
        {
            //new drawing, need new plugin
            p->plugins[drawingName] = p->thread.getWidget()->loadPlugin("", "DrawingVisualization");;
            assert(p->plugins[drawingName] != null);
        }
        
        //NOTE DirectConnection should be fine because updateData is designed to be called from a non-gui thread
        QMetaObject::invokeMethod(p->plugins[drawingName], "updateData", Qt::DirectConnection,
                                  Q_ARG(vizkit3dDebugDrawings::Drawing, d));
    }
    
    void DrawingManager::removeDrawing(const std::string& drawingName)
    {
    }
}
