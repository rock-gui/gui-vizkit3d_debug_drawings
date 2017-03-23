#include "DrawingManager.h"
#include "Drawing.h"
#include "PlotDataPoint.h"
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
        std::unordered_map<std::string, QObject*> drawingPlugins;
        std::unordered_map<std::string, QObject*> plotPlugins;
        
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
            throw  std::runtime_error("drawingName is empty");
        }
        Drawing& d = p->drawings[drawingName];
        d.addPrimitive(primitive);
        d.setName(drawingName); //d might be a new Drawing
        
        if(p->drawingPlugins.find(drawingName) == p->drawingPlugins.end())
        {
            //new drawing, need new plugin
            p->drawingPlugins[drawingName] = loadPlugin("DrawingVisualization");
            assert(p->drawingPlugins[drawingName] != nullptr);
        }
        
        updateData(d);
    }
    
    void DrawingManager::addPlotDataPoint(const std::string& drawingName,
                                          const base::Vector2d& dataPoint)
    {
        if(drawingName.empty())
        {
            throw  std::runtime_error("drawingName is empty");
        }
        
        if(p->plotPlugins.find(drawingName) == p->plotPlugins.end())
        {
            //new drawing, need new plugin
            p->plotPlugins[drawingName] = loadPlugin("DebugPlotVisualization");
            assert(p->plotPlugins[drawingName] != nullptr);
        }
        
        const PlotDataPoint d{drawingName, dataPoint};        
        updateData(d);
    }
    
    void DrawingManager::removeDrawing(const std::string& drawingName)
    {
        if(drawingName.empty())
        {
            throw  std::runtime_error("drawingName is empty");
        }
        
        p->drawings.erase(drawingName);
        
        if(p->drawingPlugins.find(drawingName) != p->drawingPlugins.end())
        {
            //async invoke slot to avoid any threading issues with the gui thread
            QMetaObject::invokeMethod(p->widget, "removePlugin", Qt::QueuedConnection,
                                  Q_ARG(QObject*, p->drawingPlugins[drawingName]));
            p->drawingPlugins.erase(drawingName);
        }
        
        //FIXME duplicate code?!
        if(p->plotPlugins.find(drawingName) != p->plotPlugins.end())
        {
            QMetaObject::invokeMethod(p->widget, "removePlugin", Qt::QueuedConnection,
                                  Q_ARG(QObject*, p->plotPlugins[drawingName]));
            p->plotPlugins.erase(drawingName);
        }
        
    }
    
    void DrawingManager::clearDrawing(const std::string& drawingName)
    {
        if(drawingName.empty())
        {
            throw std::runtime_error("drawingName is empty");
        }
        
        if(p->drawings.find(drawingName) != p->drawings.end())
        {
            p->drawings[drawingName].clear();
            updateData(p->drawings[drawingName]);
        }
        
        //FIXME how to clear plot?
        
    }
    
    void DrawingManager::clearAllDrawings()
    {
        for(auto drawingKeyValuePair : p->drawings)
        {
            drawingKeyValuePair.second.clear();
        }
        
        //FIXME how to clear plots?
    }   
    
    void DrawingManager::updateData(const Drawing& d) const
    {
        QObject* plugin = p->drawingPlugins[d.getName()];
        
        //NOTE DirectConnection should be fine because updateData is designed to be called from a non-gui thread
        QMetaObject::invokeMethod(plugin, "updateData", Qt::DirectConnection,
                                  Q_ARG(vizkit3dDebugDrawings::Drawing, d));
    }
    
    void DrawingManager::updateData(const PlotDataPoint& d) const
    {
        QObject* plugin = p->plotPlugins[d.name];
        
        //NOTE DirectConnection should be fine because updateData is designed to be called from a non-gui thread
        QMetaObject::invokeMethod(plugin, "updateData", Qt::DirectConnection,
                                  Q_ARG(vizkit3dDebugDrawings::PlotDataPoint, d));
    }

    
    vizkit3d::VizPluginBase* DrawingManager::loadPlugin(const std::string& pluginName)
    {
        //use queded connection if we are not in gui thread
        const Qt::ConnectionType conType = QThread::currentThread() == getVizkit3DWidget()->thread()? Qt::DirectConnection : Qt::BlockingQueuedConnection; 
        QObject* plugin = nullptr;
        QMetaObject::invokeMethod(getVizkit3DWidget(), "loadPlugin", conType,
                                  Q_RETURN_ARG(QObject*, plugin),
                                  Q_ARG(QString, ""), Q_ARG(QString, QString::fromStdString(pluginName)));
        return dynamic_cast<vizkit3d::VizPluginBase*>(plugin);
    }
}
