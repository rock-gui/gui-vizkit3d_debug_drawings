#pragma once
#include "vizkit3d_debug_drawings/commands/DrawCommand.hpp"
#include <string>
#include <Eigen/Core>
#include "vizkit3d_debug_drawings/commands/BoostSerializationHelpers.hpp"
#include <boost/serialization/vector.hpp>

namespace osg
{
    class Node;
}

namespace vizkit3dDebugDrawings
{
class DrawPolyLineCommand : public DrawCommand
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<DrawCommand>(*this);
        ar & position;
        ar & points;
        ar & colorRGBA;
    }
    
    
public:
    DrawPolyLineCommand();
    
    DrawPolyLineCommand(const std::string& drawingGroupName, const Eigen::Vector3d& position, const Eigen::Vector4d& colorRGBA);
        
    std::vector<Eigen::Vector3d>& getPoints();
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawPolyLineCommand* clone() const;
    
private:
    Eigen::Vector3d position;
    std::vector<Eigen::Vector3d> points;
    Eigen::Vector4d colorRGBA;
    
};
}
