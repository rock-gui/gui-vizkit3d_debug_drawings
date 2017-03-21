#include <iostream>
#include "DebugPlotVisualization.hpp"
#include <QLabel>
#include "qcustomplot/qcustomplot.h"

using namespace vizkit3d;

struct DebugPlotVisualization::Data {
    vizkit3dDebugDrawings::PlotDrawing data;
    QDockWidget* dock;
    QCustomPlot* plot;
};


DebugPlotVisualization::DebugPlotVisualization()
    : p(new Data)
{
    p->plot = new QCustomPlot();
    p->dock = new QDockWidget("default name");
    p->dock->setWidget(p->plot);
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
    p->dock->setWindowTitle(QString(p->data.name.c_str()));
}

void DebugPlotVisualization::updateDataIntern(vizkit3dDebugDrawings::PlotDrawing const& value)
{
    p->data = value;
    emit propertyChanged("name");
}

QString DebugPlotVisualization::getName() const
{
    return QString(p->data.name.c_str());
}

void DebugPlotVisualization::createDockWidgets()
{
    dockWidgets.push_back(p->dock);
}



//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(DebugPlotVisualization)

