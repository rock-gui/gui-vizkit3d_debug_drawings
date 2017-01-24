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
    class DrawingManager
    {
    public:
        static DrawingManager* instance();
        
        /** Adds @p prim to the drawing named @p drawingName.
         * If @p drawingName does not exist, it is created.
         * @param drawingName May not be empty*/
        void addPrimitive(const std::string& drawingName, const osg::ref_ptr<osgviz::Object>&);
      
        /** Removes the specified drawing */
        void removeDrawing(const std::string& drawingName);
        
        /**Returns the Vizkit3DWidget instance that is used by the DrawingManager.  */
        vizkit3d::Vizkit3DWidget* getVizkit3DWidget() const;
        
    private:
        DrawingManager();
        /**Use pimpl idiom to hide as much of the implementation details as possible because this
         * class might be included in a lot of projects. Thus changes to the header would cause lots
         * of recompiling that we don't want.*/
        struct PImpl;
        std::unique_ptr<PImpl> p;
    };
}