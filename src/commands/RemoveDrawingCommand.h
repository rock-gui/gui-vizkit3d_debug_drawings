#pragma once
#include <string>
#include "Command.h"
#include <boost/serialization/base_object.hpp>

namespace vizkit3dDebugDrawings
{
    
/**A command that removes a given drawing*/
class RemoveDrawingCommand : public Command
{
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<Command>(*this);
        ar & drawingName;
    }
    
public:
    RemoveDrawingCommand(const std::string& drawingName);   
    RemoveDrawingCommand();
    virtual void execute(DrawingManager* drawingManager) const;
    const std::string& getDrawingName() const;    
    virtual ~RemoveDrawingCommand();
    virtual RemoveDrawingCommand* clone() const;
    
    
private:
    /**The name of the drawing that should be removed*/
    std::string drawingName;
};
}
