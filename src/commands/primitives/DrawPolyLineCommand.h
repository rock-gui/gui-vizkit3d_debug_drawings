#pragma once
#include <vizkit3d_debug_drawings/commands/DrawCommand.h>
#include <string>
#include <base/Eigen.hpp>
#include <boost_serialization/EigenTypes.hpp>
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
    
    DrawPolyLineCommand(const std::string& drawingName, const base::Vector3d& position, const base::Vector4d& colorRGBA);
        
    std::vector<base::Vector3d>& getPoints();
    
    virtual osg::ref_ptr<osgviz::Object> createPrimitive() const;
    
    virtual DrawPolyLineCommand* clone() const;
    
private:
    base::Vector3d position;
    std::vector<base::Vector3d> points;
    base::Vector4d colorRGBA;
    
};
}
