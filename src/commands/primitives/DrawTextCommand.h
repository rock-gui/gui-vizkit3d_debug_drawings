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
    
    DrawTextCommand(const std::string& drawingName, const base::Vector3d& position,
                    const base::Quaterniond& orientation, const std::string& text,
                    double fontSize, const base::Vector4d& colorRGBA);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
private:
    base::Vector3d position;
    base::Quaterniond orientation;
    std::string text;
    double fontSize;
    base::Vector4d colorRGBA;
    
};
}
