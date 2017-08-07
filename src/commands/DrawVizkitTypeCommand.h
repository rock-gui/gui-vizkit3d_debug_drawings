#pragma once
#include <string>
#include "Command.h"
#include <boost/serialization/base_object.hpp>
#include <boost_serialization/EigenTypes.hpp>
#include <base/Eigen.hpp>
#include <vector>

namespace osgviz
{
    class Object;
}

namespace vizkit3dDebugDrawings
{
    
/**A command that draws a primitive */
class DrawVizkitTypeCommand : public Command
{
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<Command>(*this);
        ar & position;
        ar & orientation;
        ar & typeName;
        //TODO somehow serialize data using typekit?
        ar & data;
    }
    
public:
    DrawVizkitTypeCommand(const std::string& drawingName, const base::Vector3d& position,
                          const base::Quaterniond& orientation, const std::string& typeName,
                          void* pData);
    DrawVizkitTypeCommand();
    
    virtual void execute(DrawingManager* drawingManager) const;

    virtual DrawVizkitTypeCommand* clone() const;
    
    virtual ~DrawVizkitTypeCommand();
    
private:
    
    /**Marshal @p pData into @p data as type @p typeName */
    void marshall(const std::string& typeName, void* pData);

    /** Unmarshall from @p data.
     * @note User is responsible for deleting the pointer*/
    void* unmarshall() const;
    
    base::Vector3d position;
    base::Quaterniond orientation;
    std::string typeName;
    std::vector<uint8_t> data;
};
}



