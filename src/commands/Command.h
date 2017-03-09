#pragma once
#include <boost/serialization/access.hpp>

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
        {}
        
    public:
        /** Execute this command on the @p drawingManager*/
        virtual void execute(DrawingManager* drawingManager) const;
        virtual ~Command();
        
        /**Creates a virtual copy of this instance.
         * This method needs to be reimplemented in all base classes.
         * @see virtual copy constructor idiom: https://isocpp.org/wiki/faq/virtual-functions#virtual-ctors
         */
        virtual Command* clone() const;
    };
}