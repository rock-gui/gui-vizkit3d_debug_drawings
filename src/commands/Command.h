#pragma once

namespace vizkit3dDebugDrawings
{
    class DrawingManager;

    /**A serializable command that can be sent to the DrawingManager */
    class Command
    {
        friend class DrawingManager;
    public:
        /** Execute this command on the @p drawingManager*/
        virtual void execute(DrawingManager* drawingManager) const;
        virtual ~Command();
    };
}