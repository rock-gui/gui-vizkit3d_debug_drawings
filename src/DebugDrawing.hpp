#pragma once

/**This is the main header that should be included to use debug drawings.
 * It defines all required macros */

#ifndef ENABLE_DEBUG_DRAWINGS


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
    void CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(...){}
#endif
    void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(...){}
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
}
#else
 

#include <string>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "DebugDrawingColors.hpp"


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
 * 
 * NOTE: Everything debug drawing related is thread local. I.e. debug drawings are
 *       configured on a per thread basis. This is especially important when 
 *       using drawings from inside tasks because the hooks are not necessarily 
 *       executed in the same thread.  */

    /**@throw std::runtime_error if already configured */
    void CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget* widget);

#ifdef USE_PORTS    
    void CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext); 
    /**Same as above but does nothing if already configured. */
    void CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(RTT::TaskContext* taskContext);
#endif
    
    /**Same as above but does nothing if already configured */
    void CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(vizkit3d::Vizkit3DWidget* widget);

    /** @param position center of the box  */
    void DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                            const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                            const Eigen::Vector4d& colorRGBA);
    
    /** @param position center of the box*/
    void DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                            const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);
    
    /** @param position Position of the tip of the arrow
     *  @param orientation Identity points in z-direction*/
    void DRAW_ARROW(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                    const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                    const Eigen::Vector4d& colorRGBA);
    
    /** @param position Position of the tip of the arrow */
    void DRAW_ARROW(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                    const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);

    void DRAW_RING(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, double radius,
                   double height, double thickness, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_RING(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   double radius, double height, double thickness, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_SPHERE(const std::string& drawingGroupName, double posX, double posY, double posZ,
                     double radius, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_SPHERE(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                     double radius, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_CYLINDER(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                       const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                       const Eigen::Vector4d& colorRGBA);
    
    void DRAW_CYLINDER(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                       const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);
    
    /** @param position origin of the line
     *  @param points relative to @p position.*/
    void DRAW_POLYLINE(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                       const std::vector<Eigen::Vector3d>& points, const Eigen::Vector4d& colorRGBA);
    
    /** @param points realtive to (0, 0, 0) */
    void DRAW_POLYLINE(const std::string& drawingGroupName, const std::vector<Eigen::Vector3d>& points,
                       const Eigen::Vector4d& colorRGBA);
    
    /** @param from relative to (0, 0, 0)
     *  @param to   relative to (0, 0, 0) */
    void DRAW_LINE(const std::string& drawingGroupName, const Eigen::Vector3d& from, const Eigen::Vector3d& to,
                   const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
                   double rotW, double rotX, double rotY, double rotZ,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    
    /** @param position position of the center of the axes */
    void DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size);
    
    void DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation);
    
    void DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position);
    
    /** draw axis aligned bounding box */
    void DRAW_AABB(const std::string& drawingGroupName, Eigen::AlignedBox3d box,
                   const Eigen::Vector4d& colorRGBA);

    void PLOT_2D(const std::string& plotName, const Eigen::Vector2d& dataPoint);
    
    void CLEAR_PLOT(const std::string& plotName);
    
    /** Removes the drawing.
     * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
     * @note If you want to animate something, use CLEAR_DRAWING instead.*/
    void REMOVE_DRAWING(const std::string& drawingGroupName);
    
    /** Removes the content from a drawing but keeps the drawing itself.
     * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
     * Use this if you want to animate movements.*/
    void CLEAR_DRAWING(const std::string& drawingGroupName);
    
    /**Flush the drawing buffer */
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


