#define ENABLE_DEBUG_DRAWINGS //to get the right version of the header
#include "commands/primitives/DrawSphereCommand.h"
#include "commands/primitives/DrawTextCommand.h"
#include "commands/primitives/DrawRingCommand.h"
#include "commands/primitives/DrawWireframeBoxCommand.h"
#include "commands/primitives/DrawArrowCommand.h"
#include "commands/primitives/DrawPolyLineCommand.h"
#include "commands/primitives/DrawCylinderCommand.h"
#include "commands/primitives/DrawAxesCommand.h"
#include "commands/primitives/DrawAABBCommand.h"
#include "commands/RemoveDrawingCommand.h"
#include "commands/ClearDrawingCommand.h"
#include "commands/PlotCommand.h"
#include "commands/ClearPlotCommand.h"
#include <vizkit3d_debug_drawings/commands/CommandBuffer.h>

#include "dispatch/CommandDispatcherFactory.hpp"
#include <vizkit3d/Vizkit3DWidget.hpp>


using namespace vizkit3dDebugDrawings;


void V3DD_DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                        const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                        const Eigen::Vector4d& colorRGBA)
{
    DrawWireframeBoxCommand cmd(drawingGroupName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);     
}

void V3DD_DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                        const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_WIREFRAME_BOX(drawingGroupName, position, Eigen::Quaterniond::Identity(), size, colorRGBA);
}


void V3DD_DRAW_ARROW(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                const Eigen::Vector4d& colorRGBA)
{
    DrawArrowCommand cmd(drawingGroupName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);   
}


void V3DD_DRAW_ARROW(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_ARROW(drawingGroupName, position, Eigen::Quaterniond::Identity(), size, colorRGBA);
}


void V3DD_DRAW_RING(const std::string& drawingGroupName, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, double radius,
               double height, double thickness, const Eigen::Vector4d& colorRGBA) 
{ 
    DrawRingCommand cmd(drawingGroupName, position, orientation, height, thickness, radius,
                        colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

void V3DD_DRAW_RING(const std::string& drawingGroupName, const Eigen::Vector3d& position,
               double radius, double height, double thickness, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_RING(drawingGroupName, position, Eigen::Quaterniond::Identity(), radius,
              height, thickness, colorRGBA);
}

void V3DD_DRAW_SPHERE(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                 double radius, const Eigen::Vector4d& colorRGBA)
{
    DrawSphereCommand cmd(drawingGroupName, position, radius, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void V3DD_DRAW_SPHERE(const std::string& drawingGroupName, double posX, double posY, double posZ,
                 double radius, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_SPHERE(drawingGroupName, Eigen::Vector3d(posX, posY, posZ), radius, colorRGBA);
}

void V3DD_DRAW_POLYLINE(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const std::vector<Eigen::Vector3d>& points, const Eigen::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingGroupName, position, colorRGBA);
    cmd.getPoints().insert(cmd.getPoints().begin(), points.begin(), points.end());
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

/** @param points realtive to (0, 0, 0) */
void V3DD_DRAW_POLYLINE(const std::string& drawingGroupName, const std::vector<Eigen::Vector3d>& points,
                   const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_POLYLINE(drawingGroupName, Eigen::Vector3d(0, 0, 0), points, colorRGBA);
}


void V3DD_DRAW_TEXT(const std::string& drawingGroupName, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, const std::string& text,
               double fontSize, const Eigen::Vector4d& colorRGBA)
{
    
    DrawTextCommand cmd(drawingGroupName, position, orientation, text, fontSize, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void V3DD_DRAW_TEXT(const std::string& drawingGroupName, const Eigen::Vector3d& position,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_TEXT(drawingGroupName, position, Eigen::Quaterniond::Identity(), text, fontSize, colorRGBA);
}

void V3DD_DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_TEXT(drawingGroupName, Eigen::Vector3d(posX, posY, posZ), Eigen::Quaterniond(rotW, rotX, rotY, rotZ),
                                          text, fontSize, colorRGBA);    
}

void V3DD_DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_TEXT(drawingGroupName, Eigen::Vector3d(posX, posY, posZ), Eigen::Quaterniond::Identity(),
                                          text, fontSize, colorRGBA);     
}

void V3DD_DRAW_LINE(const std::string& drawingGroupName, const Eigen::Vector3d& from, const Eigen::Vector3d& to,
               const Eigen::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingGroupName, Eigen::Vector3d(0, 0, 0), colorRGBA);
    cmd.getPoints().push_back(from);
    cmd.getPoints().push_back(to);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

void V3DD_DRAW_CYLINDER(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                   const Eigen::Vector4d& colorRGBA)
{
    DrawCylinderCommand cmd(drawingGroupName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd); 
}

void V3DD_DRAW_CYLINDER(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
    V3DD_DRAW_CYLINDER(drawingGroupName, position, Eigen::Quaterniond::Identity(), size, colorRGBA);
}


void V3DD_DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size)
{
    DrawAxesCommand cmd(drawingGroupName,position, orientation, size);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void V3DD_DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation)
{
    V3DD_DRAW_AXES(drawingGroupName, position, orientation, Eigen::Vector3d(1, 1, 1));
}

void V3DD_DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position)
{
    V3DD_DRAW_AXES(drawingGroupName, position, Eigen::Quaterniond::Identity());
}

void V3DD_DRAW_AABB(const std::string& drawingGroupName, Eigen::AlignedBox3d box, 
               const Eigen::Vector4d& colorRGBA)
{

    DrawAABBCommand cmd(drawingGroupName, box.min(), box.max(), colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}


void V3DD_PLOT_2D(const std::string& drawingGroupName, const Eigen::Vector2d& dataPoint)
{
    PlotCommand cmd(drawingGroupName, dataPoint);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void V3DD_CLEAR_PLOT(const std::string& plotName)
{
    ClearPlotCommand cmd(plotName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void V3DD_REMOVE_DRAWING(const std::string& drawingGroupName)
{
    RemoveDrawingCommand cmd(drawingGroupName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);      
}

void V3DD_CLEAR_DRAWING(const std::string& drawingGroupName)
{
    ClearDrawingCommand cmd(drawingGroupName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);  
}

void V3DD_FLUSH_DRAWINGS()
{
    CommandDispatcherFactory::getThreadLocalInstance()->flush(); 
}

void V3DD_CONFIGURE_DEBUG_DRAWINGS_STANDALONE()
{
    CommandDispatcherFactory::createStandaloneDispatcher();
}

void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget * widget)
{
    CommandDispatcherFactory::createWidgetDispatcher(widget);
}

#ifdef USE_PORTS
void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext)
{
    CommandDispatcherFactory::createPortDispatcher(taskContext);
}

void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(RTT::TaskContext* taskContext)
{
    if(!CommandDispatcherFactory::instanceExists())
        CommandDispatcherFactory::createPortDispatcher(taskContext);
}
#endif

void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(vizkit3d::Vizkit3DWidget* widget)
{
    if(!CommandDispatcherFactory::instanceExists())
        CommandDispatcherFactory::createWidgetDispatcher(widget);
}
