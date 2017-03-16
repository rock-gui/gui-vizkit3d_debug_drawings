#pragma once
#include <boost/serialization/access.hpp>

#include <string>
namespace vizkit3dDebugDrawings
{
    class DrawingManager;

    /**A serializable command that can be sent to the DrawingManager */
    class Command
    {
        friend class DrawingManager;
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & drawingName;
        }
        
        /**The name (unique id) of the drawing that this primitive belongs to */
        std::string drawingName;
        
    public:
        /** Execute this command on the @p drawingManager*/
        virtual void execute(DrawingManager* drawingManager) const;
        Command(const std::string& drawingName);
        Command();
        
        virtual ~Command();
        
 
        /**Creates a virtual copy of this instance.
         * This method needs to be reimplemented in all base classes.
         * @see virtual copy constructor idiom: https://isocpp.org/wiki/faq/virtual-functions#virtual-ctors
         */
        virtual Command* clone() const;
        
        virtual const std::string& getDrawingName() const;
    };
}