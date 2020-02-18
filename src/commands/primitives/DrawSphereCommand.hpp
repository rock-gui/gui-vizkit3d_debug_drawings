#pragma once
#include "commands/DrawCommand.hpp"
#include <string>
#include <Eigen/Core>
#include "commands/BoostSerializationHelpers.hpp"

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DrawSphereCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & position;
        ar & radius;
        ar & colorRGBA;
    }
    
    
    
public:
    DrawSphereCommand();
    
    DrawSphereCommand(const std::string& drawingChannel, const Eigen::Vector3d& position, double radius,
                      const Eigen::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawSphereCommand* clone() const;
    
private:
    Eigen::Vector3d position;
    double radius;
    Eigen::Vector4d colorRGBA;

};
}
