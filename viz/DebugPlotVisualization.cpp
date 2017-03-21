#include <iostream>
#include "DebugPlotVisualization.hpp"
#include <QLabel>
#include "qcustomplot/qcustomplot.h"
#include <deque>
#include <base/Eigen.hpp>

using namespace vizkit3d;

struct DebugPlotVisualization::Data {
    std::deque<base::Vector2d> data;
    QDockWidget* dock;
    QCustomPlot* plot;
    std::string plotName;
};


DebugPlotVisualization::DebugPlotVisualization()
    : p(new Data)
{
    p->plot = new QCustomPlot();
    p->plot->addGraph();
//     p->plot->setInteraction(QCP::iRangeDrag, true);
//     p->plot->setInteraction(QCP::iRangeZoom, true);
    
    p->plot->setContextMenuPolicy(Qt::CustomContextMenu);
    
    p->dock = new QDockWidget("default name");
    p->dock->setWidget(p->plot);
    
    connect(this, SIGNAL(replot()), p->plot, SLOT(replot()));
    connect(p->plot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    
    
}

void DebugPlotVisualization::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(p->plot);
  menu->setAttribute(Qt::WA_DeleteOnClose);
  menu->addAction("autoScroll", this, SLOT(testSlot()));//->setData((int)(Qt::AlignTop|Qt::AlignLeft));
   
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
        std::cout << p->data.front().transpose() << "\n";
        p->plot->graph(0)->addData(p->data.front().x(), p->data.front().y());
        p->plot->xAxis->setRange(p->data.front().x() - 6, p->data.front().x() + 1);
        p->data.pop_front();
    }
    
    
    if(plotNeedsRedraw)
    {
        
        emit replot();//need to do this in gui thread, otherwise recursive redraw occurs
    }
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

