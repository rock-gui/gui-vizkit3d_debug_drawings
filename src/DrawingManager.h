#pragma once
#include <string>
#include <memory>
#include <osg/ref_ptr>

namespace vizkit3d 
{
    class Vizkit3DWidget;
}
namespace osgviz
{
    class Object;
}

namespace vizkit3dDebugDrawings
{   
    class Drawing;
    
    class DrawingManager
    {
    public:
        static DrawingManager* instance();
        
        /** Adds @p prim to the drawing named @p drawingName.
         * If @p drawingName does not exist, it is created.
         * @param drawingName May not be empty*/
        void addPrimitive(const std::string& drawingName, const osg::ref_ptr<osgviz::Object>&);
      
        /** Removes the drawing.
         * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
         * @note If you want to animate something, use CLEAR_DRAWING instead.*/
        void removeDrawing(const std::string& drawingName);
        
        /** Removes the content from a drawing but keeps the drawing itself.
         * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
         * Use this if you want to animate movements.*/
        void clearDrawing(const std::string& drawingName);
        
        /**Returns the Vizkit3DWidget instance that is used by the DrawingManager.  */
        vizkit3d::Vizkit3DWidget* getVizkit3DWidget() const;
        
    private:
        DrawingManager();
        /**Use pimpl idiom to hide as much of the implementation details as possible because this
         * class might be included in a lot of projects. Thus changes to the header would cause lots
         * of recompiling that we don't want.*/
        
        /** invokes updateData() on the vizkit3d plugin belonging to @p d.
         * @note plugin needs to exist before.*/
        void updateData(const Drawing& d) const;
        
        struct PImpl;
        std::unique_ptr<PImpl> p;
    };
}