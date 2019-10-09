#pragma once
#include <string>
#include "Command.hpp"
#include <osg/ref_ptr>
#include <boost/serialization/base_object.hpp>

namespace osgviz
{
    class Object;
}

namespace vizkit3dDebugDrawings
{
    
/**A command that draws a primitive */
class DrawCommand : public Command
{
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<Command>(*this);
    }
    
public:
    DrawCommand(const std::string& drawingGroupName);
    
    /**Creates an osgviz::Object that represents the drawing*/
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const = 0;
    
    virtual void execute(DrawingManager* drawingManager) const;

    virtual DrawCommand* clone() const;
    
    virtual ~DrawCommand();
};
}
