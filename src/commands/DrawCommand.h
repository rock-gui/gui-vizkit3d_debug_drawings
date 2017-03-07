#pragma once
#include <string>
#include "Command.h"
#include <osg/ref_ptr>

namespace osgviz
{
    class Object;
}

namespace vizkit3dDebugDrawings
{
    
/**A command that draws something using the drawing manager */
class DrawCommand : public Command
{
public:
    
    DrawCommand(const std::string& drawingName);
    
    /**Creates an osgviz::Object that represents the drawing*/
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const = 0;
    virtual void execute(DrawingManager* drawingManager) const;
    /** @return The name (unique id) of the drawing that this primitive belongs to */
    const std::string& getDrawingName() const;
    
    virtual ~DrawCommand();
    
private:
    /**The drawing that this primitive belongs to */
    std::string drawingName;
};
}
