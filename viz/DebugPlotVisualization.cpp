#include <iostream>
#include "DebugPlotVisualization.hpp"
#include <QLabel>
#include <rock_widget_collection/qcustomplot.h>
#include <deque>
#include <base/Eigen.hpp>
#include <QAction>
#include <mutex>

using namespace vizkit3d;

struct DebugPlotVisualization::Data {
    std::deque<base::Vector2d> data;
    std::mutex dataMutex;
    QDockWidget* dock;
    QCustomPlot* plot;
    std::string plotName;
    QAction* autoScrollAction;
    QTimer timer;
    const size_t maxSamples = 20000; //maximum number of samples that is displayed
    const size_t removeSamples = 2000; //number of samples that is removd if maxSamples is reached
};


DebugPlotVisualization::DebugPlotVisualization()
    : p(new Data)
{
    p->plot = new QCustomPlot();
    p->plot->addGraph();
    p->plot->setContextMenuPolicy(Qt::CustomContextMenu);
    
    p->dock = new QDockWidget("default name");
    p->dock->setWidget(p->plot);
    
    p->autoScrollAction = new QAction("auto scroll", p->plot);
    p->autoScrollAction->setCheckable(true);
    p->autoScrollAction->setChecked(true);
    p->autoScrollAction->setToolTip("Use mouse to zoom and drag if auto scroll is disabled");
    
    connect(p->autoScrollAction, SIGNAL(triggered()), this, SLOT(autoScrollChecked()));
    connect(p->plot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    connect(&p->timer, SIGNAL(timeout()), this, SLOT(updateUi()));
    
    p->timer.start(250);
} 

void DebugPlotVisualization::autoScrollChecked()
{
    setAutoscroll(p->autoScrollAction->isChecked());
}

void DebugPlotVisualization::setAutoscroll(bool enable)
{
    if(!enable)
    {
        p->plot->setRangeDrag(Qt::Horizontal | Qt::Vertical);
        p->plot->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    }
    else
    {
        p->plot->setRangeDrag(0);
        p->plot->setRangeZoom(0);
    }
}

void DebugPlotVisualization::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(p->plot);
//   menu->setAttribute(Qt::WA_DeleteOnClose);
  menu->addAction(p->autoScrollAction);
   
  menu->popup(p->plot->mapToGlobal(pos));
}


DebugPlotVisualization::~DebugPlotVisualization()
{
    //dtor needs to be defined for unique_ptr pimpl idiom to compile
    
    //if dock is not managed by qt, delete it manually
    if(p->dock->parent() == nullptr)
        delete p->dock;
}

osg::ref_ptr<osg::Node> DebugPlotVisualization::createMainNode()
{
    return new osg::Group();
}

void DebugPlotVisualization::updateUi()
{
    const bool plotNeedsRedraw = !p->data.empty();
    
    while(!p->data.empty())
    {
        base::Vector2d dataPoint;
        {
            std::lock_guard<std::mutex> lock(p->dataMutex);
            dataPoint = p->data.front();
            p->data.pop_front();
        }
        
        p->plot->graph(0)->addData(dataPoint.x(), dataPoint.y());
        
        if(p->plot->graph(0)->data()->size() > p->maxSamples)
        {
            //removing data is expensive, therefore we remove bigger batches at once
            const double removeKey = (p->plot->graph(0)->data()->begin() + p->removeSamples)->key;
            p->plot->graph(0)->removeDataBefore(removeKey);
        }
        
        //if auto scroll
        if(p->autoScrollAction->isChecked())
        {
            p->plot->xAxis->setRange(dataPoint.x() - 6, dataPoint.x() + 1);
            p->plot->graph(0)->rescaleValueAxis();
        }
    }
    
    if(plotNeedsRedraw)
    {
        //invoke to avoid calling repaint from a timer thread
        //For some reason this works while emitting a signal does not, no idea why
        QMetaObject::invokeMethod(p->plot, "replot", Qt::QueuedConnection);
    }
    
}

void DebugPlotVisualization::updateMainNode(osg::Node* node)
{
    p->dock->setWindowTitle(QString(p->plotName.c_str()));
}


void DebugPlotVisualization::updateDataIntern(vizkit3dDebugDrawings::PlotDataPoint const& value)
{
    {
        std::lock_guard<std::mutex> lock(p->dataMutex);
        p->data.push_back(value.data);
    }
    
    if(p->plotName != value.name)
    {
        p->plotName = value.name;
        emit propertyChanged("name");
    }
}

QString DebugPlotVisualization::getName() const
{
    return QString(p->plotName.c_str());
}

void DebugPlotVisualization::createDockWidgets()
{
    dockWidgets.push_back(p->dock);
}



//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(DebugPlotVisualization)

