/** This file registers all commands with boost serialization.
 *  If you want to serialize a command using a base class pointer, you need to include this file.
 *  If you add new commands, they need to be added in here.
 */

#pragma once

#include "Command.h"
#include "DrawCommand.h"
#include "RemoveDrawingCommand.h"
#include "ClearDrawingCommand.h"
#include "PlotCommand.h"
#include "primitives/DrawArrowCommand.h"
#include "primitives/DrawCylinderCommand.h"
#include "primitives/DrawPolyLineCommand.h"
#include "primitives/DrawRingCommand.h"
#include "primitives/DrawSphereCommand.h"
#include "primitives/DrawTextCommand.h"
#include "primitives/DrawWireframeBoxCommand.h"

//NOTE needs to be included last
#include <boost/serialization/export.hpp>


BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawRingCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawArrowCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawCylinderCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawPolyLineCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawSphereCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawWireframeBoxCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawTextCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::Command);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::ClearDrawingCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::RemoveDrawingCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::PlotCommand);