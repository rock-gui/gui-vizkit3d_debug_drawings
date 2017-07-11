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


void DRAW_WIREFRAME_BOX(const std::string& drawingName, const base::Vector3d& position,
                        const base::Quaterniond& orientation, const base::Vector3d& size,
                        const base::Vector4d& colorRGBA)
{
    DrawWireframeBoxCommand cmd(drawingName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);     
}

void DRAW_WIREFRAME_BOX(const std::string& drawingName, const base::Vector3d& position,
                        const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_WIREFRAME_BOX(drawingName, position, base::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_ARROW(const std::string& drawingName, const base::Vector3d& position,
                const base::Quaterniond& orientation, const base::Vector3d& size,
                const base::Vector4d& colorRGBA)
{
    DrawArrowCommand cmd(drawingName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);   
}


void DRAW_ARROW(const std::string& drawingName, const base::Vector3d& position,
                const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_ARROW(drawingName, position, base::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_RING(const std::string& drawingName, const base::Vector3d& position,
               const base::Quaterniond& orientation, double radius,
               double height, double thickness, const base::Vector4d& colorRGBA) 
{ 
    DrawRingCommand cmd(drawingName, position, orientation, height, thickness, radius,
                        colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

void DRAW_RING(const std::string& drawingName, const base::Vector3d& position,
               double radius, double height, double thickness, const base::Vector4d& colorRGBA)
{
    DRAW_RING(drawingName, position, base::Quaterniond::Identity(), radius,
              height, thickness, colorRGBA);
}

void DRAW_SPHERE(const std::string& drawingName, const base::Vector3d& position,
                 double radius, const base::Vector4d& colorRGBA)
{
    DrawSphereCommand cmd(drawingName, position, radius, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void DRAW_SPHERE(const std::string& drawingName, double posX, double posY, double posZ,
                 double radius, const base::Vector4d& colorRGBA)
{
    DRAW_SPHERE(drawingName, base::Vector3d(posX, posY, posZ), radius, colorRGBA);
}

void DRAW_POLYLINE(const std::string& drawingName, const base::Vector3d& position,
                   const std::vector<base::Vector3d>& points, const base::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingName, position, colorRGBA);
    cmd.getPoints().insert(cmd.getPoints().begin(), points.begin(), points.end());
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

/** @param points realtive to (0, 0, 0) */
void DRAW_POLYLINE(const std::string& drawingName, const std::vector<base::Vector3d>& points,
                   const base::Vector4d& colorRGBA)
{
    DRAW_POLYLINE(drawingName, base::Vector3d(0, 0, 0), points, colorRGBA);
}


void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& position,
               const base::Quaterniond& orientation, const std::string& text,
               double fontSize, const base::Vector4d& colorRGBA)
{
    
    DrawTextCommand cmd(drawingName, position, orientation, text, fontSize, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& position,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, position, base::Quaterniond::Identity(), text, fontSize, colorRGBA);
}

void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, base::Vector3d(posX, posY, posZ), base::Quaterniond(rotW, rotX, rotY, rotZ),
                                          text, fontSize, colorRGBA);    
}

void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const base::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingName, base::Vector3d(posX, posY, posZ), base::Quaterniond::Identity(),
                                          text, fontSize, colorRGBA);     
}

void DRAW_LINE(const std::string& drawingName, const base::Vector3d& from, const base::Vector3d& to,
               const base::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingName, base::Vector3d(0, 0, 0), colorRGBA);
    cmd.getPoints().push_back(from);
    cmd.getPoints().push_back(to);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);    
}

void DRAW_CYLINDER(const std::string& drawingName, const base::Vector3d& position,
                   const base::Quaterniond& orientation, const base::Vector3d& size,
                   const base::Vector4d& colorRGBA)
{
    DrawCylinderCommand cmd(drawingName, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd); 
}

void DRAW_CYLINDER(const std::string& drawingName, const base::Vector3d& position,
                   const base::Vector3d& size, const base::Vector4d& colorRGBA)
{
    DRAW_CYLINDER(drawingName, position, base::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_AXES(const std::string& drawingName, const base::Vector3d& position,
               const base::Quaterniond& orientation, const base::Vector3d& size)
{
    DrawAxesCommand cmd(drawingName,position, orientation, size);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void DRAW_AXES(const std::string& drawingName, const base::Vector3d& position,
               const base::Quaterniond& orientation)
{
    DRAW_AXES(drawingName, position, orientation, base::Vector3d(1, 1, 1));
}

void DRAW_AXES(const std::string& drawingName, const base::Vector3d& position)
{
    DRAW_AXES(drawingName, position, base::Quaterniond::Identity());
}

void DRAW_AABB(const std::string& drawingName, Eigen::AlignedBox3d box, 
               const base::Vector4d& colorRGBA)
{

    DrawAABBCommand cmd(drawingName, box.min(), box.max(), colorRGBA);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}


void DRAW_VIZKIT3D_TYPE(const std::string& drawingName, const base::Vector3d& position,
                        const base::Quaterniond& orientation, const std::string& typeName,
                        void* data)
{
    DrawVizkitTypeCommand cmd(drawingName, position, orientation, typeName, data);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void PLOT_2D(const std::string& drawingName, const base::Vector2d& dataPoint)
{
    PlotCommand cmd(drawingName, dataPoint);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

void CLEAR_PLOT(const std::string& plotName)
{
    ClearPlotCommand cmd(plotName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);
}

/** Removes the drawing.
 * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
 * @note If you want to animate something, use CLEAR_DRAWING instead.*/
void REMOVE_DRAWING(const std::string& drawingName)
{
    RemoveDrawingCommand cmd(drawingName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);      
}

/** Removes the content from a drawing but keeps the drawing itself.
 * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
 * Use this if you want to animate movements.*/
void CLEAR_DRAWING(const std::string& drawingName)
{
    ClearDrawingCommand cmd(drawingName);
    CommandDispatcherFactory::getThreadLocalInstance()->dispatch(cmd);  
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


