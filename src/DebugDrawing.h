#pragma once

/**This is the main header that should be included to use debug drawings.
 * It defines all required macros */

#ifndef ENABLE_DEBUG_DRAWINGS

    #define V3DD_CONFIGURE_DEBUG_DRAWINGS_STANDALONE(...)  (void)0
    #define V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(...)  (void)0
    #define V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_PORT(...)  (void)0
    #define V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(...)  (void)0
    #define V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(...)  (void)0
    
    #define V3DD_DRAW_RING(...) (void)0
    #define V3DD_DRAW_PRIMITIVE(...) (void)0
    #define V3DD_DRAW_WIREFRAME_BOX(...) (void) 0
    #define V3DD_REMOVE_DRAWING(...) (void) 0
    #define V3DD_CLEAR_DRAWING(...) (void) 0
    #define V3DD_DRAW_SPHERE(...) (void)0
    #define V3DD_DRAW_POLYLINE(...) (void)0
    #define V3DD_DRAW_TEXT(...) (void)0
    #define V3DD_DRAW_LINE(...) (void)0
    #define V3DD_DRAW_AXES(...) (void)0
    #define V3DD_DRAW_AABB(...) (void)0
    #define V3DD_DRAW_ARROW(...) (void)0
    #define V3DD_DRAW_CYLINDER(...) (void)0
    #define V3DD_PLOT_2D(...) (void)0
    #define V3DD_CLEAR_PLOT(...) (void)0
    #define V3DD_FLUSH_DRAWINGS(...) (void)0
    
    #define V3DD_COMPLEX_DRAWING(...) (void)0
    
    
#else

#include <string>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "DebugDrawingColors.h"


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
    void V3DD_CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET(vizkit3d::Vizkit3DWidget* widget);

#ifdef USE_PORTS    
    void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_PORT(RTT::TaskContext* taskContext); 
    /**Same as above but does nothing if already configured. */
    void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_PORT_NO_THROW(RTT::TaskContext* taskContext);
#endif
    
    /**Same as above but does nothing if already configured */
    void V3DD_CONFIGURE_DEBUG_DRAWINGS_USE_EXISTING_WIDGET_NO_THROW(vizkit3d::Vizkit3DWidget* widget);
    
    #define V3DD_DECLARE_DEBUG_DRAWING(drawingGroupName) \
        namespace V3DD_STATIC_DECLARATIONS \
        { \
            class V3DD_STATIC_DECLARE_##drawingGroupName_INITIALIZER \
            { \
                public: V3DD_STATIC_DECLARE_##drawingGroupName_INITIALIZER() \
                { \
                    std::cout << "TEEEEEEEEEEEEEEEEST" << std::endl; \
                    std::cout << "TEEEEEEEEEEEEEEEEST" << std::endl; \
                    std::cout << "TEEEEEEEEEEEEEEEEST" << std::endl; \
                    std::cout << "TEEEEEEEEEEEEEEEEST" << std::endl; \
                    std::cout << "TEEEEEEEEEEEEEEEEST" << std::endl; \
                    std::cout << "TEEEEEEEEEEEEEEEEST" << std::endl; \
                }\
            };\
            V3DD_STATIC_DECLARE_##drawingGroupName_INITIALIZER init_##drawingGroupName = V3DD_STATIC_DECLARE_##drawingGroupName_INITIALIZER(); \
        }
    

    
    //TODO
    void V3DD_DECLARE_DEBUG_PLOT(const std::string& plotName);

    /** @param position center of the box  */
    void V3DD_DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                            const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                            const Eigen::Vector4d& colorRGBA);
    
    /** @param position center of the box*/
    void V3DD_DRAW_WIREFRAME_BOX(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                            const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);
    
    /** @param position Position of the tip of the arrow
     *  @param orientation Identity points in z-direction*/
    void V3DD_DRAW_ARROW(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                    const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                    const Eigen::Vector4d& colorRGBA);
    
    /** @param position Position of the tip of the arrow */
    void V3DD_DRAW_ARROW(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                    const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);

    void V3DD_DRAW_RING(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, double radius,
                   double height, double thickness, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_RING(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   double radius, double height, double thickness, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_SPHERE(const std::string& drawingGroupName, double posX, double posY, double posZ,
                     double radius, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_SPHERE(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                     double radius, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_CYLINDER(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                       const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                       const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_CYLINDER(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                       const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA);
    
    /** @param position origin of the line
     *  @param points relative to @p position.*/
    void V3DD_DRAW_POLYLINE(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                       const std::vector<Eigen::Vector3d>& points, const Eigen::Vector4d& colorRGBA);
    
    /** @param points realtive to (0, 0, 0) */
    void V3DD_DRAW_POLYLINE(const std::string& drawingGroupName, const std::vector<Eigen::Vector3d>& points,
                       const Eigen::Vector4d& colorRGBA);
    
    /** @param from relative to (0, 0, 0)
     *  @param to   relative to (0, 0, 0) */
    void V3DD_DRAW_LINE(const std::string& drawingGroupName, const Eigen::Vector3d& from, const Eigen::Vector3d& to,
                   const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_TEXT(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_TEXT(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
                   double rotW, double rotX, double rotY, double rotZ,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    void V3DD_DRAW_TEXT(const std::string& drawingGroupName, double posX, double posY, double posZ,
                   const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA);
    
    
    /** @param position position of the center of the axes */
    void V3DD_DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size);
    
    void V3DD_DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation);
    
    void V3DD_DRAW_AXES(const std::string& drawingGroupName, const Eigen::Vector3d& position);
    
    /** draw axis aligned bounding box */
    void V3DD_DRAW_AABB(const std::string& drawingGroupName, Eigen::AlignedBox3d box,
                   const Eigen::Vector4d& colorRGBA);

    void V3DD_PLOT_2D(const std::string& plotName, const Eigen::Vector2d& dataPoint);
    
    void V3DD_CLEAR_PLOT(const std::string& plotName);
    
    /** Removes the drawing.
     * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
     * @note If you want to animate something, use CLEAR_DRAWING instead.*/
    void V3DD_REMOVE_DRAWING(const std::string& drawingGroupName);
    
    /** Removes the content from a drawing but keeps the drawing itself.
     * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
     * Use this if you want to animate movements.*/
    void V3DD_CLEAR_DRAWING(const std::string& drawingGroupName);
    
    /**Flush the drawing buffer */
    void V3DD_FLUSH_DRAWINGS();
    
    /**Use this if debug drawings need additional code that is only required for the drawing.
     * @note This is scoped. I.e. variables created in here cannot be referenced from other scopes*/
    #define V3DD_COMPLEX_DRAWING(...) do { __VA_ARGS__; } while (0)

#endif


