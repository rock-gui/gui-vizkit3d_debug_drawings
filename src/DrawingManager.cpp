#include "DrawingManager.hpp"
#include "Drawing.hpp"
#include "PlotDataPoint.hpp"
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
    
    void DrawingManager::addPrimitive(const std::string& drawingChannel, const osg::ref_ptr<osgviz::Object>& primitive)
    {
        checkStringNotEmpty(drawingChannel);

        Drawing& d = p->drawings[drawingChannel];
        d.addPrimitive(primitive);
        d.setName(drawingChannel); //d might be a new Drawing
        
        if(p->drawingPlugins.find(drawingChannel) == p->drawingPlugins.end())
        {
            //new drawing, need new plugin
            p->drawingPlugins[drawingChannel] = loadPlugin("DrawingVisualization");
            assert(p->drawingPlugins[drawingChannel] != nullptr);
        }
        
        updateData(d);
    }
    
    void DrawingManager::addPlotDataPoint(const std::string& plotName,
                                          const Eigen::Vector2d& dataPoint)
    {
        checkStringNotEmpty(plotName);
        
        if(p->plotPlugins.find(plotName) == p->plotPlugins.end())
        {
            //new drawing, need new plugin
            p->plotPlugins[plotName] = loadPlugin("DebugPlotVisualization");
            assert(p->plotPlugins[plotName] != nullptr);
        }
        
        const PlotDataPoint d{plotName, dataPoint};        
        updateData(d);
    }
    
    void DrawingManager::clearPlot(const std::string& plotName)
    {
        checkStringNotEmpty(plotName);
        
        auto plotPlugin = p->plotPlugins.find(plotName);
        if(plotPlugin != p->plotPlugins.end())
        {
            //async invoke slot to avoid any threading issues with the gui thread
            QMetaObject::invokeMethod(plotPlugin->second, "clearData", Qt::QueuedConnection);
        }
    }

    
    void DrawingManager::removeDrawing(const std::string& drawingChannel)
    {
        checkStringNotEmpty(drawingChannel);
        
        p->drawings.erase(drawingChannel);
        
        if(p->drawingPlugins.find(drawingChannel) != p->drawingPlugins.end())
        {
            //async invoke slot to avoid any threading issues with the gui thread
            QMetaObject::invokeMethod(p->widget, "removePlugin", Qt::QueuedConnection,
                                  Q_ARG(QObject*, p->drawingPlugins[drawingChannel]));
            p->drawingPlugins.erase(drawingChannel);
        }
    }
    
    void DrawingManager::clearDrawing(const std::string& drawingChannel)
    {
        checkStringNotEmpty(drawingChannel);
        
        if(p->drawings.find(drawingChannel) != p->drawings.end())
        {
            p->drawings[drawingChannel].clear();
            updateData(p->drawings[drawingChannel]);
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
    
    void DrawingManager::checkStringNotEmpty(const std::string& str)
    {
        if(str.empty())
        {
            throw std::runtime_error("drawingChannel is empty");
        }
    }

    
}
