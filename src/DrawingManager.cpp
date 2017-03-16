#include "DrawingManager.h"
#include "Drawing.h"
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
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
        vizkit3d::Vizkit3DWidget* widget = nullptr;
    };
    
    DrawingManager::DrawingManager(vizkit3d::Vizkit3DWidget* widget) : p(new PImpl())
    {
        p->widget = widget;
    }
    
    DrawingManager::~DrawingManager()
    {}
    
        
    vizkit3d::Vizkit3DWidget* DrawingManager::getVizkit3DWidget() const
    {
        return p->widget;
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
            p->plugins[drawingName] = loadPlugin();
            assert(p->plugins[drawingName] != nullptr);
        }
        
        updateData(d);
    }
    
    void DrawingManager::addPlot(const std::string& drawingName, double plotVal)
    {
        
    }
    
    void DrawingManager::removeDrawing(const std::string& drawingName)
    {
        if(drawingName.empty())
        {
            throw new std::runtime_error("drawingName is empty");
        }
        
        p->drawings.erase(drawingName);
        
        if(p->plugins.find(drawingName) != p->plugins.end())
        {
            //async invoke slot to avoid any threading issues with the gui thread
            QMetaObject::invokeMethod(p->widget, "removePlugin", Qt::QueuedConnection,
                                  Q_ARG(QObject*, p->plugins[drawingName]));
            p->plugins.erase(drawingName);
        }
    }
    
    void DrawingManager::clearDrawing(const std::string& drawingName)
    {
        if(drawingName.empty())
        {
            throw new std::runtime_error("drawingName is empty");
        }
        
        if(p->drawings.find(drawingName) != p->drawings.end())
        {
            p->drawings[drawingName].clear();
            updateData(p->drawings[drawingName]);
        }
    }
    
    void DrawingManager::clearAllDrawings()
    {
        for(auto drawingKeyValuePair : p->drawings)
        {
            drawingKeyValuePair.second.clear();
        }
    }   
    
    void DrawingManager::updateData(const Drawing& d) const
    {
        //NOTE DirectConnection should be fine because updateData is designed to be called from a non-gui thread
        QMetaObject::invokeMethod(p->plugins[d.getName()], "updateData", Qt::DirectConnection,
                                  Q_ARG(vizkit3dDebugDrawings::Drawing, d));
    }
    
    vizkit3d::VizPluginBase* DrawingManager::loadPlugin()
    {
        //use queded connection if we are not in gui thread
        const Qt::ConnectionType conType = QThread::currentThread() == getVizkit3DWidget()->thread()? Qt::DirectConnection : Qt::BlockingQueuedConnection; 
        QObject* plugin = nullptr;
        QMetaObject::invokeMethod(getVizkit3DWidget(), "loadPlugin", conType,
                                  Q_RETURN_ARG(QObject*, plugin),
                                  Q_ARG(QString, ""), Q_ARG(QString, "DrawingVisualization"));
        return dynamic_cast<vizkit3d::VizPluginBase*>(plugin);
    }
}
