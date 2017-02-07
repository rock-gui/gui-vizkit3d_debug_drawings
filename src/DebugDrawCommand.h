#pragma once
#include <string>

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DebugDrawCommand
{
public:
    virtual void draw(osg::Node* node) = 0;
    
    const std::string& getDrawingName() const
    {
        return drawingName;
    }
    
private:
    /**The drawing that this command belongs to */
    std::string drawingName;
};
}
