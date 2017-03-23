#pragma once

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <vizkit3d_debug_drawings/PlotDataPoint.h>
#include<memory>


namespace vizkit3d
{
    //visualizes plots in a dock widget
    class DebugPlotVisualization
        : public vizkit3d::Vizkit3DPlugin<vizkit3dDebugDrawings::PlotDataPoint>
        , boost::noncopyable
    {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName)
    public:
        DebugPlotVisualization();
        ~DebugPlotVisualization();

    Q_INVOKABLE void updateData(vizkit3dDebugDrawings::PlotDataPoint const &sample)
    {vizkit3d::Vizkit3DPlugin<vizkit3dDebugDrawings::PlotDataPoint>::updateData(sample);}
    
    QString getName() const;

    private slots:
        void contextMenuRequest(QPoint);
        void autoScrollChecked();
        void updateUi();//refreshes the ui

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(vizkit3dDebugDrawings::PlotDataPoint const& drawing);
        virtual void createDockWidgets();
        
    private:
        
        void setAutoscroll(bool enable);
        
        struct Data;
        std::unique_ptr<Data> p;
    };
}