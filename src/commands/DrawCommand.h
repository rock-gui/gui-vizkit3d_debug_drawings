#pragma once
#include <string>
#include "Command.h"
#include <osg/ref_ptr>
#include <boost/serialization/base_object.hpp>

namespace osgviz
{
    class Object;
}

namespace vizkit3dDebugDrawings
{
    
/**A command that draws something using the drawing manager */
class DrawCommand : public Command
{
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<Command>(*this);
        ar & drawingName;
    }
    
public:
    
    DrawCommand(const std::string& drawingName);
    
    /**Creates an osgviz::Object that represents the drawing*/
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const = 0;
    
    virtual void execute(DrawingManager* drawingManager) const;
    
    /** @return The name (unique id) of the drawing that this primitive belongs to */
    const std::string& getDrawingName() const;
    
    virtual DrawCommand* clone() const;
    
    virtual ~DrawCommand();
    
private:
    /**The drawing that this primitive belongs to */
    std::string drawingName;
};
}
