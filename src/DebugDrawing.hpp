#pragma once

/**This is the main header that should be included to use debug drawings.
 * It defines all required macros */

#ifndef ENABLE_DEBUG_DRAWINGS
#include <string>
#include <vector>

namespace vizkit3d
{
    class Vizkit3DWidget;
}

namespace RTT
{
    class TaskContext;
}

namespace v3dd_internal
{
    class CommandBuffer;
}


///////////////////////
// This block contains the disabled versions of the functions. They do nothing and will be optimized out.
// See below for the real functions and documentation
///////////////////////
namespace V3DD
{
    void CONFIGURE_DEBUG_DRAWINGS_STANDALONE(){}
    void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(...){}

#ifdef USE_PORTS    
    void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(...){}
#endif
    void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(...){}
    
    #define V3DD_DECLARE_DEBUG_DRAWING_CHANNEL(...)
    
    void DRAW_WIREFRAME_BOX(...){}
    void DRAW_ARROW(...){}
    void DRAW_RING(...){}
    void DRAW_SPHERE(...){}
    void DRAW_CYLINDER(...){}
    void DRAW_POLYLINE(...){}
    void DRAW_LINE(...){}
    void DRAW_TEXT(...){}
    void DRAW_AXES(...){}
    void DRAW_AABB(...){}
    void PLOT_2D(...){}
    void CLEAR_PLOT(...){}
    void REMOVE_DRAWING(...){}
    void CLEAR_DRAWING(...){}
    void FLUSH_DRAWINGS(){}
    void COMPLEX_DRAWING(...){}
    std::vector<std::string> GET_DECLARED_CHANNELS(){return std::vector<std::string>();}
}
#else
 

#include <string>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "DebugDrawingColors.hpp"
#include "DeclaredChannels.hpp"
#include "StaticDeclarationHelpers.hpp"


namespace vizkit3d
{
    class Vizkit3DWidget;
}
namespace RTT
{
    class TaskContext;
}
namespace vizkit3dDebugDrawings
{
    class CommandBuffer;
}

#define V3DD_DECLARE_DEBUG_DRAWING_CHANNEL(channel) \
namespace vizkit3dDebugDrawings \
{ \
    static StaticDeclareChannel V3DD_INTERNAL_CONCAT(staticChannel, __COUNTER__) = StaticDeclareChannel(channel); \
}

namespace V3DD
{
/**
 *  *** Configuration ***
 *  Debug drawings need to be configured before beeing displayed.
 *  Up to 100000 drawings are buffered until configuration has taken place.
 *  Once configured the buffered drawings will be displayed and all further 
 *  drawings will be drawn immediately.
 *  
 *  Following configurations are possible:
 *  * standalone:
 *    In standalone mode a qt application is created in a seperate thread.
 *    All drawings are displayed in a Vizkit3dWidget managed by that application.
 * 
 *  * using an existing vizkit3d widget:
 *    In this mode it is assumed that a qt application is already running and a
 *    Vizkit3dWidget exists somewhere. That widget is used to display all 
 *    drawings.
 * 
 *  * via rock ports:
 *    In this mode rock ports will be created for all drawings.
 *    A vizkit3d plugin can be used to display the drawings.
 *    This mode requires some configuration steps. 
 *    Please read the corresponding chapter of the documentation.
 *   */

    /**@throw std::runtime_error if already configured */
    void CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget* widget);

#ifdef USE_PORTS    
    /** Configure debug drawings to output the @p drawingChannels as ports on the given @p taskContext.*/
    void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext,
        const std::vector<std::string>& drawingChannels); 

#endif
    
    
    /** Returns a list of all drawing channels that have been declared for the given @p prefix
     *  @param outChannels will contain the declared channels after this call*/
    std::vector<std::string> GET_DECLARED_CHANNELS();

    /** @param position center of the box  */
    void DRAW_WIREFRAME_BOX(const std::string& drawingChannel, const Eigen::Vector3d& position,
                            const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                            const Eigen::Vector4d& colorRGBA);
    
    /** @param position center of the box*/
    void DRAW_WIREFRAME_BOX(const std::string& drawingChannel, const Eigen::Vector3d& position,
                            const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);
    
    /** @param position Position of the tip of the arrow
     *  @param orientation Identity points in z-direction*/
    void DRAW_ARROW(const std::string& drawingChannel, const Eigen::Vector3d& position,
                    const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                    const Eigen::Vector4d& colorRGBA);

    /** @param position Position of the tip of the arrow */
    void DRAW_ARROW(const std::string& drawingChannel, const Eigen::Vector3d& position,
                    const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);

    void DRAW_RING(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, double radius,
                   double height, double thickness, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_RING(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   double radius, double height, double thickness, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_SPHERE(const std::string& drawingChannel, double posX, double posY, double posZ,
                     double radius, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_SPHERE(const std::string& drawingChannel, const Eigen::Vector3d& position,
                     double radius, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_CYLINDER(const std::string& drawingChannel, const Eigen::Vector3d& position,
                       const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                       const Eigen::Vector4d& colorRGBA);
    
    void DRAW_CYLINDER(const std::string& drawingChannel, const Eigen::Vector3d& position,
                       const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);
    
    /** @param position origin of the line
     *  @param points relative to @p position.*/
    void DRAW_POLYLINE(const std::string& drawingChannel, const Eigen::Vector3d& position,
                       const std::vector<Eigen::Vector3d>& points, const Eigen::Vector4d& colorRGBA);
    
    /** @param points realtive to (0, 0, 0) */
    void DRAW_POLYLINE(const std::string& drawingChannel, const std::vector<Eigen::Vector3d>& points,
                       const Eigen::Vector4d& colorRGBA);
    
    /** @param from relative to (0, 0, 0)
     *  @param to   relative to (0, 0, 0) */
    void DRAW_LINE(const std::string& drawingChannel, const Eigen::Vector3d& from, const Eigen::Vector3d& to,
                   const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingChannel, double posX, double posY, double posZ,
                   double rotW, double rotX, double rotY, double rotZ,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingChannel, double posX, double posY, double posZ,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    
    /** @param position position of the center of the axes */
    void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size);
    
    void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation);
    
    void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position);
    
    /** draw axis aligned bounding box */
    void DRAW_AABB(const std::string& drawingChannel, Eigen::AlignedBox3d box,
                   const Eigen::Vector4d& colorRGBA);

    void PLOT_2D(const std::string& plotName, const Eigen::Vector2d& dataPoint);
    
    void CLEAR_PLOT(const std::string& plotName);
    
    /** Removes the drawing channel.
     * I.e. unloades the vizkit3d plugin responsible for rendering this drawing and removes all drawings.
     * @note If you want to animate something, use CLEAR_DRAWING instead.*/
    void REMOVE_DRAWING(const std::string& drawingChannel);
    
    /** Removes the content from a drawing channel but keeps the channel itself.
     * I.e. the visualizer itself will be kept and the users settings will be retained.
     * Use this if you want to animate movements.*/
    void CLEAR_DRAWING(const std::string& drawingChannel);
    
    /**Flush the drawing channel buffer.
     * Flushing may not be needed depending on your use case. See documentation!*/
    void FLUSH_DRAWINGS();
    
    /**Use this if debug drawings need additional code that is only required for the drawing.
     * See documentation for example*/
    template <class T>
    void COMPLEX_DRAWING(T&& f)
    {
        f();
    }
}

#endif


