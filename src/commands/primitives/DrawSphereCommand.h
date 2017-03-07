#pragma once
#include <vizkit3d_debug_drawings/commands/DrawCommand.h>

#pragma once
#include <string>
#include <base/Eigen.hpp>

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DrawSphereCommand : public DrawCommand
{
public:
    DrawSphereCommand(const std::string& drawingName, const base::Vector3d& position, double radius,
                      const base::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
private:
    const base::Vector3d position;
    const double radius;
    const base::Vector4d colorRGBA;

};
}
