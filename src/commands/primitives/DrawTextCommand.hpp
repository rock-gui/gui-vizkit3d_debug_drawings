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
class DrawTextCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & position;
        ar & orientation;
        ar & text;
        ar & fontSize;
        ar & colorRGBA;
    }
    

    
public:
    DrawTextCommand();
    
    DrawTextCommand(const std::string& drawingChannel, const Eigen::Vector3d& position,
                    const Eigen::Quaterniond& orientation, const std::string& text,
                    double fontSize, const Eigen::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawTextCommand* clone() const;
    
private:
    Eigen::Vector3d position;
    Eigen::Quaterniond orientation;
    std::string text;
    double fontSize;
    Eigen::Vector4d colorRGBA;
    
};
}
