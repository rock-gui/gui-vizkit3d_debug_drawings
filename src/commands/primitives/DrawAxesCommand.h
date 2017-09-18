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
class DrawAxesCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & position;
        ar & orientation;
        ar & scale;
    }
    
public:
    DrawAxesCommand();
    
    DrawAxesCommand(const std::string& drawingGroupName, const base::Vector3d& position,
                     const base::Quaterniond& orientation, const base::Vector3d& scale);
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawAxesCommand* clone() const;
    
private:
    base::Vector3d position;
    base::Quaterniond orientation;
    base::Vector3d scale;

};
}
