#pragma once
#include "ICommandDispatcher.hpp"
#include <vizkit3d/QtThreadedWidget.hpp>
#include <vizkit3d/Vizkit3DWidget.hpp>
#include "../DrawingManager.hpp"

namespace vizkit3dDebugDrawings
{
class StandaloneDispatcher : public ICommandDispatcher
{
public:
    
    StandaloneDispatcher();
    virtual void dispatch(const Command& cmd);

    virtual void flush();
private:
    QtThreadedWidget<vizkit3d::Vizkit3DWidget> thread; 
    std::unique_ptr<DrawingManager> drawingManager;//need to use pointer due to lazy initiaization
};
}
