#pragma once

/**This is the main header that should be included to use debug drawings.
 * It defines all required macros */

#ifndef ENABLE_DEBUG_DRAWINGS

    #define DRAW_RING(...) (void)0
    #define DRAW_PRIMITIVE(...) (void)0
    #define DRAW_WIREFRAME_BOX(...) (void) 0
    #define REMOVE_DRAWING(...) (void) 0
    #define CLEAR_DRAWING(...) (void) 0
    #define DRAW_SPHERE(...) (void)0
    #define DRAW_POLYLINE(...) (void)0
    #define DRAW_TEXT(...) (void)0
    
    
    #define COMPLEX_DRAWING(...) (void)0
    
    
    
#else

#include <string>
#include "DrawingManager.h"
#include <osgViz/modules/viz/Primitives/PrimitivesFactory.h>
#include <osgViz/OsgViz.hpp>
#include <vector>
#include <base/Eigen.hpp>

    /**Draws any osgviz object
     * @param prim Pointer to osgviz::Object 
     */
    void DRAW_PRIMITIVE(const std::string& drawingName, double posX, double posY, double posZ,
                        double rotW, double rotX, double rotY, double rotZ, osg::ref_ptr<osgviz::Object> prim);

    void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ,
                            double rotW, double rotX, double rotY, double rotZ, double xSize,
                            double ySize, double zSize, const base::Vector4d& colorRGBA);
    
    void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY, double posZ,
                            double xSize, double ySize, double zSize, const base::Vector4d& colorRGBA);
    
    void DRAW_WIREFRAME_BOX(const std::string& drawingName, double posX, double posY,
                            double posZ, const base::Vector4d& colorRGBA);
    
    void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                            double rotW, double rotX, double rotY, double rotZ, double xScale,
                    double yScale, double zScale, const base::Vector4d& colorRGBA);
    
    void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ,
                    double xScale, double yScale, double zScale, const base::Vector4d& colorRGBA);
    
    void DRAW_ARROW(const std::string& drawingName, double posX, double posY, double posZ, const base::Vector4d& colorRGBA);
    
    void DRAW_RING(const std::string& drawingName, double posX, double posY, double posZ,
                   double rotW, double rotX, double rotY, double rotZ, double radius,
                   double height, double thickness, const base::Vector4d& colorRGBA);
    
    void DRAW_RING(const std::string& drawingName, double posX, double posY, double posZ,
                   double radius, double height, double thickness, const base::Vector4d& colorRGBA);
    
    void DRAW_SPHERE(const std::string& drawingName, double posX, double posY, double posZ,
                     double radius, const base::Vector4d& colorRGBA);
    
    void DRAW_POLYLINE(const std::string& drawingName, double posX, double posY, double posZ,
                       const std::vector<base::Vector3d>& points, const base::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
                   double rotW, double rotX, double rotY, double rotZ,
                   const std::string& text, double fontSize, const base::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingName, double posX, double posY, double posZ,
                   const std::string& text, double fontSize, const base::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& pos,
                   const base::Quaterniond& rot, const std::string& text, double fontSize, const base::Vector4d& colorRGBA);
    
    void DRAW_TEXT(const std::string& drawingName, const base::Vector3d& pos,
                   const std::string& text, double fontSize, const base::Vector4d& colorRGBA);
    
    /** Removes the drawing.
     * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
     * @note If you want to animate something, use CLEAR_DRAWING instead.*/
    void REMOVE_DRAWING(const std::string& drawingName);
    
    /** Removes the content from a drawing but keeps the drawing itself.
     * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
     * Use this if you want to animate movements.*/
    void CLEAR_DRAWING(const std::string& drawingName);
    
    /**Use this if debug drawings need additional code that is only required for the drawing */
    #define COMPLEX_DRAWING(...) do { __VA_ARGS__; } while (0)
    

#endif


