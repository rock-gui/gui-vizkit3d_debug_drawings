#pragma once
#include <vizkit3d_debug_drawings/commands/DrawCommand.hpp>

#pragma once
#include <string>
#include <Eigen/Core>
#include <vizkit3d_debug_drawings/commands/BoostSerializationHelpers.hpp>

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DrawRingCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & position;
        ar & orientation;
        ar & height;
        ar & thickness;
        ar & radius;
        ar & colorRGBA;
    }
    
    
    
public:
    DrawRingCommand();
    
    DrawRingCommand(const std::string& drawingChannel, const Eigen::Vector3d& position,
                    const Eigen::Quaterniond& orientation, double height,
                    double thickness, double radius, const Eigen::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawRingCommand* clone() const;
    
private:
    Eigen::Vector3d position;
    Eigen::Quaterniond orientation;
    double height;
    double thickness;
    double radius;
    Eigen::Vector4d colorRGBA;
    
};
}
