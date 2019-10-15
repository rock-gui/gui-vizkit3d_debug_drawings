#pragma once
#include <vizkit3d_debug_drawings/commands/DrawCommand.hpp>
#include <string>
#include <Eigen/Core>
#include <vizkit3d_debug_drawings/commands/BoostSerializationHelpers.hpp>

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
    
    DrawAABBCommand(const std::string& drawingChannel, const Eigen::Vector3d& min,
                    const Eigen::Vector3d& max, const Eigen::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawAABBCommand* clone() const;
    
private:
    Eigen::Vector3d min;
    Eigen::Vector3d max;
    Eigen::Vector4d colorRGBA;
};
}
