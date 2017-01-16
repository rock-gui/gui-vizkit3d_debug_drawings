#ifndef vizkit3dDebugDrawings_DrawingVisualization_H
#define vizkit3dDebugDrawings_DrawingVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <vizkit3dDebugDrawings/Drawing.h>

namespace vizkit3d
{
    class DrawingVisualization
        : public vizkit3d::Vizkit3DPlugin<vizkti3dDebugDrawings::Drawing>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        DrawingVisualization();
        ~DrawingVisualization();

    Q_INVOKABLE void updateData(vizkti3dDebugDrawings::Drawing const &sample)
    {vizkit3d::Vizkit3DPlugin<vizkti3dDebugDrawings::Drawing>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(vizkti3dDebugDrawings::Drawing const& plan);
        
    private:
        struct Data;
        Data* p;
    };
}
#endif
