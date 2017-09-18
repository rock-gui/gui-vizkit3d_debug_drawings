#pragma once
#include <vizkit3d_debug_drawings/commands/DrawCommand.h>
#include <string>
#include <base/Eigen.hpp>
#include <boost_serialization/EigenTypes.hpp>

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DrawAABBCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & min;
        ar & max;
        ar & colorRGBA;
    }
    
public:
    DrawAABBCommand();
    
    DrawAABBCommand(const std::string& drawingGroupName, const base::Vector3d& min,
                    const base::Vector3d& max, const base::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawAABBCommand* clone() const;
    
private:
    base::Vector3d min;
    base::Vector3d max;
    base::Vector4d colorRGBA;
};
}
