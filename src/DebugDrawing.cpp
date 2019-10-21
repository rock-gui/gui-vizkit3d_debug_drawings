#define ENABLE_DEBUG_DRAWINGS //to get the right version of the header
#include "commands/primitives/DrawSphereCommand.hpp"
#include "commands/primitives/DrawTextCommand.hpp"
#include "commands/primitives/DrawRingCommand.hpp"
#include "commands/primitives/DrawWireframeBoxCommand.hpp"
#include "commands/primitives/DrawArrowCommand.hpp"
#include "commands/primitives/DrawPolyLineCommand.hpp"
#include "commands/primitives/DrawCylinderCommand.hpp"
#include "commands/primitives/DrawAxesCommand.hpp"
#include "commands/primitives/DrawAABBCommand.hpp"
#include "commands/RemoveDrawingCommand.hpp"
#include "commands/ClearDrawingCommand.hpp"
#include "commands/PlotCommand.hpp"
#include "commands/ClearPlotCommand.hpp"
#include <vizkit3d_debug_drawings/commands/CommandBuffer.hpp>

#include "dispatch/CommandDispatcherFactory.hpp"
#include <vizkit3d/Vizkit3DWidget.hpp>
#include "DeclaredChannels.hpp"


using namespace vizkit3dDebugDrawings;

namespace V3DD
{

void DRAW_WIREFRAME_BOX(const std::string& drawingChannel, const Eigen::Vector3d& position,
                        const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                        const Eigen::Vector4d& colorRGBA)
{
    DrawWireframeBoxCommand cmd(drawingChannel, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);     
}

void DRAW_WIREFRAME_BOX(const std::string& drawingChannel, const Eigen::Vector3d& position,
                        const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
    DRAW_WIREFRAME_BOX(drawingChannel, position, Eigen::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_ARROW(const std::string& drawingChannel, const Eigen::Vector3d& position,
                const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                const Eigen::Vector4d& colorRGBA)
{
    DrawArrowCommand cmd(drawingChannel, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);   
}


void DRAW_ARROW(const std::string& drawingChannel, const Eigen::Vector3d& position,
                const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
    DRAW_ARROW(drawingChannel, position, Eigen::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_RING(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, double radius,
               double height, double thickness, const Eigen::Vector4d& colorRGBA) 
{ 
    DrawRingCommand cmd(drawingChannel, position, orientation, height, thickness, radius,
                        colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);    
}

void DRAW_RING(const std::string& drawingChannel, const Eigen::Vector3d& position,
               double radius, double height, double thickness, const Eigen::Vector4d& colorRGBA)
{
    DRAW_RING(drawingChannel, position, Eigen::Quaterniond::Identity(), radius,
              height, thickness, colorRGBA);
}

void DRAW_SPHERE(const std::string& drawingChannel, const Eigen::Vector3d& position,
                 double radius, const Eigen::Vector4d& colorRGBA)
{
    DrawSphereCommand cmd(drawingChannel, position, radius, colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);
}

void DRAW_SPHERE(const std::string& drawingChannel, double posX, double posY, double posZ,
                 double radius, const Eigen::Vector4d& colorRGBA)
{
    DRAW_SPHERE(drawingChannel, Eigen::Vector3d(posX, posY, posZ), radius, colorRGBA);
}

void DRAW_POLYLINE(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const std::vector<Eigen::Vector3d>& points, const Eigen::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingChannel, position, colorRGBA);
    cmd.getPoints().insert(cmd.getPoints().begin(), points.begin(), points.end());
    CommandDispatcherFactory::getInstance()->dispatch(cmd);    
}

/** @param points realtive to (0, 0, 0) */
void DRAW_POLYLINE(const std::string& drawingChannel, const std::vector<Eigen::Vector3d>& points,
                   const Eigen::Vector4d& colorRGBA)
{
    DRAW_POLYLINE(drawingChannel, Eigen::Vector3d(0, 0, 0), points, colorRGBA);
}


void DRAW_TEXT(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, const std::string& text,
               double fontSize, const Eigen::Vector4d& colorRGBA)
{
    
    DrawTextCommand cmd(drawingChannel, position, orientation, text, fontSize, colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);
}

void DRAW_TEXT(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingChannel, position, Eigen::Quaterniond::Identity(), text, fontSize, colorRGBA);
}

void DRAW_TEXT(const std::string& drawingChannel, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingChannel, Eigen::Vector3d(posX, posY, posZ), Eigen::Quaterniond(rotW, rotX, rotY, rotZ),
                                          text, fontSize, colorRGBA);    
}

void DRAW_TEXT(const std::string& drawingChannel, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
    DRAW_TEXT(drawingChannel, Eigen::Vector3d(posX, posY, posZ), Eigen::Quaterniond::Identity(),
                                          text, fontSize, colorRGBA);     
}

void DRAW_LINE(const std::string& drawingChannel, const Eigen::Vector3d& from, const Eigen::Vector3d& to,
               const Eigen::Vector4d& colorRGBA)
{
    DrawPolyLineCommand cmd(drawingChannel, Eigen::Vector3d(0, 0, 0), colorRGBA);
    cmd.getPoints().push_back(from);
    cmd.getPoints().push_back(to);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);    
}

void DRAW_CYLINDER(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                   const Eigen::Vector4d& colorRGBA)
{
    DrawCylinderCommand cmd(drawingChannel, position, orientation, size, colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd); 
}

void DRAW_CYLINDER(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
    DRAW_CYLINDER(drawingChannel, position, Eigen::Quaterniond::Identity(), size, colorRGBA);
}


void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size)
{
    DrawAxesCommand cmd(drawingChannel,position, orientation, size);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);
}

void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation)
{
    DRAW_AXES(drawingChannel, position, orientation, Eigen::Vector3d(1, 1, 1));
}

void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position)
{
    DRAW_AXES(drawingChannel, position, Eigen::Quaterniond::Identity());
}

void DRAW_AABB(const std::string& drawingChannel, Eigen::AlignedBox3d box, 
               const Eigen::Vector4d& colorRGBA)
{

    DrawAABBCommand cmd(drawingChannel, box.min(), box.max(), colorRGBA);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);
}


void PLOT_2D(const std::string& drawingChannel, const Eigen::Vector2d& dataPoint)
{
    PlotCommand cmd(drawingChannel, dataPoint);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);
}

void CLEAR_PLOT(const std::string& plotName)
{
    ClearPlotCommand cmd(plotName);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);
}

void REMOVE_DRAWING(const std::string& drawingChannel)
{
    RemoveDrawingCommand cmd(drawingChannel);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);      
}

void CLEAR_DRAWING(const std::string& drawingChannel)
{
    ClearDrawingCommand cmd(drawingChannel);
    CommandDispatcherFactory::getInstance()->dispatch(cmd);  
}

void FLUSH_DRAWINGS()
{
    CommandDispatcherFactory::getInstance()->flush(); 
}

void CONFIGURE_DEBUG_DRAWINGS_STANDALONE()
{
    CommandDispatcherFactory::createStandaloneDispatcher();
}

void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget * widget)
{
    CommandDispatcherFactory::createWidgetDispatcher(widget);

}

std::vector<std::string> GET_DECLARED_CHANNELS()
{
    const auto channels = DeclaredChannels::getInstance()->getChannels();
    std::vector<std::string> outChannels;
    for(const std::string& channel : channels)
    {
        outChannels.emplace_back(channel);
    }
    return outChannels;
}


#ifdef USE_PORTS
void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext,
        const std::vector<std::string>& drawingChannels)
{
    CommandDispatcherFactory::createPortDispatcher(taskContext, drawingChannels);
}
#endif


}
