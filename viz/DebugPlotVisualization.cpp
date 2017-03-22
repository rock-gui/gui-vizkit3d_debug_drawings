#include <iostream>
#include "DebugPlotVisualization.hpp"
#include <QLabel>
#include "qcustomplot/qcustomplot.h"
#include <deque>
#include <base/Eigen.hpp>
#include <QAction>

using namespace vizkit3d;

struct DebugPlotVisualization::Data {
    std::deque<base::Vector2d> data;
    QDockWidget* dock;
    QCustomPlot* plot;
    std::string plotName;
    QAction* autoScrollAction;
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
}

void DebugPlotVisualization::autoScrollChecked()
{
    setAutoscroll(p->autoScrollAction->isChecked());
}

void DebugPlotVisualization::setAutoscroll(bool enable)
{
    if(enable)
    {
        p->plot->setInteraction(QCP::iRangeDrag, false);
        p->plot->setInteraction(QCP::iRangeZoom, false);
    }
    else
    {
        p->plot->setInteraction(QCP::iRangeDrag, true);
        p->plot->setInteraction(QCP::iRangeZoom, true);
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
    delete p;
}

osg::ref_ptr<osg::Node> DebugPlotVisualization::createMainNode()
{
    return new osg::Group();
}

void DebugPlotVisualization::updateMainNode(osg::Node* node)
{
    p->dock->setWindowTitle(QString(p->plotName.c_str()));
    const bool plotNeedsRedraw = !p->data.empty();
    while(!p->data.empty())
    {
        p->plot->graph(0)->addData(p->data.front().x(), p->data.front().y());
        
        //if auto scroll
        if(p->autoScrollAction->isChecked())
        {
            //FIXME find better way to rescale y
            p->plot->rescaleAxes();//to scale y axis
            p->plot->xAxis->setRange(p->data.front().x() - 6, p->data.front().x() + 1);
        }
        
        p->data.pop_front(); 
    }
    
    //to avoid calling repaint recursivly (because updateMainNode might not
    //be running in the qt main thread.
    //For some reason this works while emitting a signal does not, no idea why
    QMetaObject::invokeMethod(p->plot, "replot", Qt::QueuedConnection);
}


void DebugPlotVisualization::updateDataIntern(vizkit3dDebugDrawings::PlotDrawing const& value)
{
    p->data.push_back(value.data);
    
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

