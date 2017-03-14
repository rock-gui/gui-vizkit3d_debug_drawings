#pragma once
#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <vizkit3d_debug_drawings/commands/Command.h>
#include <boost/shared_ptr.hpp>


namespace vizkit3d
{
    class DebugDrawingVisualization
        : public vizkit3d::Vizkit3DPlugin<boost::shared_ptr<vizkit3dDebugDrawings::Command>>
        , boost::noncopyable
    {
    Q_OBJECT

    public:
        DebugDrawingVisualization();
        ~DebugDrawingVisualization();

    Q_INVOKABLE void updateData(boost::shared_ptr<vizkit3dDebugDrawings::Command> const &sample)
    {vizkit3d::Vizkit3DPlugin<boost::shared_ptr<vizkit3dDebugDrawings::Command>>::updateData(sample);}


    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(boost::shared_ptr<vizkit3dDebugDrawings::Command> const& cmd);
        
    private:
        struct Data;
        Data* p;
    };
}

