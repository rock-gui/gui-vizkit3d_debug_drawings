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
#include "commands/DrawVizkitTypeCommand.h"
#include <vizkit3d_debug_drawings/commands/CommandBuffer.h>

#include "dispatch/CommandDispatcherFactory.hpp"
#include <vizkit3d/Vizkit3DWidget.hpp>


using namespace vizkit3dDebugDrawings;


void DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const base::Vector3d& position,
                        const base::Quaterniond& orientation, const base::Vector3d& size,
                        const base::Vector4d& colorRGBA)
{
    DrawWireframeBoxCommand cmd(drawingGroupName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);     
}

void DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const base::Vector3d& position,
                        const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_WIREFRAME_BOX(drawingGroupName, position, base::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_ARROW(const std::string& drawingGroupName, const base::Vector3d& position,
                const base::Quaterniond& orientation, const base::Vector3d& size,
                const base::Vector4d& colorRGBA)
{
    DrawArrowCommand cmd(drawingGroupName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);   
}


void DRAW_ARROW(const std::string& drawingGroupName, const base::Vector3d& position,
                const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_ARROW(drawingGroupName, position, base::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_RING(const std::string& drawingGroupName, const base::Vector3d& position,
               const base::Quaterniond& orientation, double radius,
               double height, double thickness, const base::Vector4d& colorRGBA) 
{ 
    DrawRingCommand cmd(drawingGroupName, position, orientation, height, thickness, radius,
                        colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

void DRAW_RING(const std::string& drawingGroupName, const base::Vector3d& position,
               double radius, double height, double thickness, const base::Vector4d& colorRGBA)
{
    DRAW_RING(drawingGroupName, position, base::Quaterniond::Identity(), radius,
              height, thickness, colorRGBA);
}

void DRAW_SPHERE(const std::string& drawingGroupName, const base::Vector3d& position,
                 double radius, const base::Vector4d& colorRGBA)
{
    DrawSphereCommand cmd(drawingGroupName, position, radius, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void DRAW_SPHERE(const std::string& drawingGroupName, double posX, double posY, double posZ,
                 double radius, const base::Vector4d& colorRGBA)
{
    DRAW_SPHERE(drawingGroupName, base::Vector3d(posX, posY, posZ), radius, colorRGBA);
}

void DRAW_POLYLINE(const std::string& drawingGroupName, const base::Vector3d& position,
                   const std::vector<base::Vector3d>& points, const base::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingGroupName, position, colorRGBA);
    cmd.getPoints().insert(cmd.getPoints().begin(), points.begin(), points.end());
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

/** @param points realtive to (0, 0, 0) */
void DRAW_POLYLINE(const std::string& drawingGroupName, const std::vector<base::Vector3d>& points,
                   const base::Vector4d& colorRGBA)
{
    DRAW_POLYLINE(drawingGroupName, base::Vector3d(0, 0, 0), points, colorRGBA);
}


void DRAW_TEXT(const std::string& drawingGroupName, const base::Vector3d& position,
               const base::Quaterniond& orientation, const std::string& text,
               double fontSize, const base::Vector4d& colorRGBA)
{
    
    DrawTextCommand cmd(drawingGroupName, position, orientation, text, fontSize, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void DRAW_TEXT(const std::string& drawingGroupName, const base::Vector3d& position,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingGroupName, position, base::Quaterniond::Identity(), text, fontSize, colorRGBA);
}

void DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingGroupName, base::Vector3d(posX, posY, posZ), base::Quaterniond(rotW, rotX, rotY, rotZ),
                                          text, fontSize, colorRGBA);    
}

void DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingGroupName, base::Vector3d(posX, posY, posZ), base::Quaterniond::Identity(),
                                          text, fontSize, colorRGBA);     
}

void DRAW_LINE(const std::string& drawingGroupName, const base::Vector3d& from, const base::Vector3d& to,
               const base::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingGroupName, base::Vector3d(0, 0, 0), colorRGBA);
    cmd.getPoints().push_back(from);
    cmd.getPoints().push_back(to);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

void DRAW_CYLINDER(const std::string& drawingGroupName, const base::Vector3d& position,
                   const base::Quaterniond& orientation, const base::Vector3d& size,
                   const base::Vector4d& colorRGBA)
{
    DrawCylinderCommand cmd(drawingGroupName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd); 
}

void DRAW_CYLINDER(const std::string& drawingGroupName, const base::Vector3d& position,
                   const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_CYLINDER(drawingGroupName, position, base::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_AXES(const std::string& drawingGroupName, const base::Vector3d& position,
               const base::Quaterniond& orientation, const base::Vector3d& size)
{
    DrawAxesCommand cmd(drawingGroupName,position, orientation, size);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void DRAW_AXES(const std::string& drawingGroupName, const base::Vector3d& position,
               const base::Quaterniond& orientation)
{
    DRAW_AXES(drawingGroupName, position, orientation, base::Vector3d(1, 1, 1));
}

void DRAW_AXES(const std::string& drawingGroupName, const base::Vector3d& position)
{
    DRAW_AXES(drawingGroupName, position, base::Quaterniond::Identity());
}

void DRAW_AABB(const std::string& drawingGroupName, Eigen::AlignedBox3d box, 
               const base::Vector4d& colorRGBA)
{

    DrawAABBCommand cmd(drawingGroupName, box.min(), box.max(), colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}


void DRAW_VIZKIT3D_TYPE(const std::string& drawingGroupName, const base::Vector3d& position,
                        const base::Quaterniond& orientation, const std::string& typeName,
                        void* data)
{
    throw std::runtime_error("DRAW_VIZKIT3D_TYPE not implemented");
//     DrawVizkitTypeCommand cmd(drawingGroupName, position, orientation, typeName, data);
//     CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void PLOT_2D(const std::string& drawingGroupName, const base::Vector2d& dataPoint)
{
    PlotCommand cmd(drawingGroupName, dataPoint);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void CLEAR_PLOT(const std::string& plotName)
{
    ClearPlotCommand cmd(plotName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void REMOVE_DRAWING(const std::string& drawingGroupName)
{
    RemoveDrawingCommand cmd(drawingGroupName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);      
}

void CLEAR_DRAWING(const std::string& drawingGroupName)
{
    ClearDrawingCommand cmd(drawingGroupName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);  
}

void FLUSH_DRAWINGS()
{
    CommandDispatcherFactory::getThreadLocalInstance()->flush(); 
}

void CONFIGURE_DEBUG_DRAWINGS_STANDALONE()
{
    CommandDispatcherFactory::createStandaloneDispatcher();
}

void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget * widget)
{
    CommandDispatcherFactory::createWidgetDispatcher(widget);
}

void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext)
{
    CommandDispatcherFactory::createPortDispatcher(taskContext);
}

void CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(RTT::TaskContext* taskContext)
{
    if(!CommandDispatcherFactory::instanceExists())
        CommandDispatcherFactory::createPortDispatcher(taskContext);
}

void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(vizkit3d::Vizkit3DWidget* widget)
{
    if(!CommandDispatcherFactory::instanceExists())
        CommandDispatcherFactory::createWidgetDispatcher(widget);
}