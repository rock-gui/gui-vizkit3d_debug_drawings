#pragma once
#include <string>
#include "Command.h"
#include <boost/serialization/base_object.hpp>
#include <Eigen/Core>
#include <boost_serialization/EigenTypes.hpp>


namespace vizkit3dDebugDrawings
{
    
/**A command that draws a primitive */
class PlotCommand : public Command
{
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<Command>(*this);
        ar & dataPoint;
    }
    
public:
    PlotCommand(const std::string& drawingGroupName, const Eigen::Vector2d& dataPoint);
    PlotCommand();
    
    virtual void execute(DrawingManager* drawingManager) const;

    virtual PlotCommand* clone() const;
    
    virtual ~PlotCommand();
    
private:
    Eigen::Vector2d dataPoint;
};
}
