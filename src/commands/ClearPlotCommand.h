#pragma once
#include <string>
#include "Command.h"
#include <boost/serialization/base_object.hpp>
#include <base/Eigen.hpp>
#include <boost_serialization/EigenTypes.hpp>


namespace vizkit3dDebugDrawings
{
    
/**A command that draws a primitive */
class ClearPlotCommand : public Command
{
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<Command>(*this);
    }
    
public:
    ClearPlotCommand(const std::string& drawingName);
    ClearPlotCommand();
    
    virtual void execute(DrawingManager* drawingManager) const;

    virtual ClearPlotCommand* clone() const;
    
    virtual ~ClearPlotCommand();
};
}
