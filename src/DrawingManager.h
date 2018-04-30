#pragma once
#include <string>
#include <memory>
#include <osg/ref_ptr>
#include <Eigen/Core>

namespace vizkit3d 
{
    class Vizkit3DWidget;
    class VizPluginBase;
}
namespace osgviz
{
    class Object;
}

namespace vizkit3dDebugDrawings
{   
    class Drawing;
    class PlotDataPoint;
    
    class DrawingManager
    {
    public:
        /** @p widget The widget that this manager should draw on */
        DrawingManager(vizkit3d::Vizkit3DWidget* widget);
        ~DrawingManager();
        
        /** Adds @p prim to the drawing named @p drawingGroupName.
         * If @p drawingGroupName does not exist, it is created.
         * @param drawingGroupName May not be empty*/
        void addPrimitive(const std::string& drawingGroupName, const osg::ref_ptr<osgviz::Object>&);
        
        void addPlotDataPoint(const std::string& plotName, const Eigen::Vector2d& dataPoint);
        
        void clearPlot(const std::string& plotName);
      
        /** Removes the drawing.
         * I.e. unloades the vizkit3d plugin responsible for rendering this drawing
         * @note If you want to animate something, use CLEAR_DRAWING instead.*/
        void removeDrawing(const std::string& drawingGroupName);
        
        /** Removes the content from a drawing but keeps the drawing itself.
         * I.e. the vizkit3d plugin will be kept and the users settings will be retained.
         * Use this if you want to animate movements.*/
        void clearDrawing(const std::string& drawingGroupName);
        
        /** Remove the content from all drawings but keep the plugins.
         *  Does not clear the plots*/
        void clearAllDrawings();
        
        /**Returns the Vizkit3DWidget instance that is used by the DrawingManager.  */
        vizkit3d::Vizkit3DWidget* getVizkit3DWidget() const;
                
    private:

        /**Use pimpl idiom to hide as much of the implementation details as possible because this
         * class might be included in a lot of projects. Thus changes to the header would cause lots
         * of recompiling that we don't want.*/
        
        /** invokes updateData() on the vizkit3d plugin belonging to @p d.
         * @note plugin needs to exist before.*/
        void updateData(const Drawing& d) const;
        
        //FIXME comment
        void updateData(const PlotDataPoint& d) const;
        
        /** @throw std::runtime_error if @p str is empty  */
        void checkStringNotEmpty(const std::string& str);
        
        /**thread safe invoke vizkit3d to load a plugin */
        vizkit3d::VizPluginBase* loadPlugin(const std::string& pluginName);
        
        struct PImpl;
        std::unique_ptr<PImpl> p;
    };
}