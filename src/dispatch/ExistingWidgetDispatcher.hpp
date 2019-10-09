#pragma once
#include "ICommandDispatcher.hpp"
#include "../DrawingManager.hpp"

namespace vizkit3d 
{
    class Vizkit3DWidget;
}

namespace vizkit3dDebugDrawings
{
class ExistingWidgetDispatcher : public ICommandDispatcher
{
public:
    
    ExistingWidgetDispatcher(vizkit3d::Vizkit3DWidget* widget);
    virtual ~ExistingWidgetDispatcher();
    virtual void dispatch(const Command& cmd);

    virtual void flush();
private:
    DrawingManager drawingManager;//need to use pointer due to lazy initiaization
};
}
