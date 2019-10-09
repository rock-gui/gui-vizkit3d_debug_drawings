#pragma once

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <vizkit3d_debug_drawings/Drawing.hpp>


namespace vizkit3d
{
    class DrawingVisualization
        : public vizkit3d::Vizkit3DPlugin<vizkit3dDebugDrawings::Drawing>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        DrawingVisualization();
        ~DrawingVisualization();

    Q_INVOKABLE void updateData(vizkit3dDebugDrawings::Drawing const &sample)
    {vizkit3d::Vizkit3DPlugin<vizkit3dDebugDrawings::Drawing>::updateData(sample);}
    
    QString getName() const;

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(vizkit3dDebugDrawings::Drawing const& drawing);
        
    private:
        struct Data;
        Data* p;
    };
}
