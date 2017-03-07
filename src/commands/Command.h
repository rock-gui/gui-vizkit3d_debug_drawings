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
    };
}