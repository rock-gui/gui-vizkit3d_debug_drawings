/** This file registers all commands with boost serialization.
 *  If you want to serialize a command using a base class pointer, you need to include this file.
 *  If you add new commands, they need to be added in here.
 */

#pragma once

#include "Command.hpp"
#include "DrawCommand.hpp"
#include "RemoveDrawingCommand.hpp"
#include "ClearDrawingCommand.hpp"
#include "PlotCommand.hpp"
#include "primitives/DrawArrowCommand.hpp"
#include "primitives/DrawCylinderCommand.hpp"
#include "primitives/DrawPolyLineCommand.hpp"
#include "primitives/DrawRingCommand.hpp"
#include "primitives/DrawSphereCommand.hpp"
#include "primitives/DrawTextCommand.hpp"
#include "primitives/DrawWireframeBoxCommand.hpp"
#include "primitives/DrawAxesCommand.hpp"
#include "primitives/DrawAABBCommand.hpp"

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
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawAxesCommand);
BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawAABBCommand);
