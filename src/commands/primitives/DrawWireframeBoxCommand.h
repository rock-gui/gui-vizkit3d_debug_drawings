#pragma once
#include <vizkit3d_debug_drawings/commands/DrawCommand.h>
#include <string>
#include <Eigen/Core>
#include <vizkit3d_debug_drawings/commands/BoostSerializationHelpers.hpp>

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DrawWireframeBoxCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & position;
        ar & orientation;
        ar & size;
        ar & colorRGBA;
    }
    

    
public:
    DrawWireframeBoxCommand();
    
    DrawWireframeBoxCommand(const std::string& drawingGroupName, const Eigen::Vector3d& position,
                            const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                            const Eigen::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawWireframeBoxCommand* clone() const;
    
private:
    Eigen::Vector3d position;
    Eigen::Quaterniond orientation;
    Eigen::Vector3d size;
    Eigen::Vector4d colorRGBA;
    
};
}
