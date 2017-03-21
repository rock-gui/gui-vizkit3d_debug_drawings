#pragma once
#include <string>
#include "Command.h"
#include <boost/serialization/base_object.hpp>



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
        ar & x;
        ar & y;
    }
    
public:
    PlotCommand(const std::string& drawingName, double x, double y);
    PlotCommand();
    
    virtual void execute(DrawingManager* drawingManager) const;

    virtual PlotCommand* clone() const;
    
    virtual ~PlotCommand();
    
private:
    double x;
    double y;
};
}
