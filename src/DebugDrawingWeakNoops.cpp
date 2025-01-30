#define ENABLE_DEBUG_DRAWINGS //to get the right version of the header
#include "DebugDrawing.hpp"

#define WEAK __attribute__((weak))


using namespace vizkit3dDebugDrawings;

namespace V3DD
{

WEAK void DRAW_WIREFRAME_BOX(const std::string& drawingChannel, const Eigen::Vector3d& position,
                        const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                        const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_WIREFRAME_BOX(const std::string& drawingChannel, const Eigen::Vector3d& position,
                        const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
}


WEAK void DRAW_ARROW(const std::string& drawingChannel, const Eigen::Vector3d& position,
                const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                const Eigen::Vector4d& colorRGBA)
{
}


WEAK void DRAW_ARROW(const std::string& drawingChannel, const Eigen::Vector3d& position,
                const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
}


WEAK void DRAW_RING(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, double radius,
               double height, double thickness, const Eigen::Vector4d& colorRGBA)
{ 
}

WEAK void DRAW_RING(const std::string& drawingChannel, const Eigen::Vector3d& position,
               double radius, double height, double thickness, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_SPHERE(const std::string& drawingChannel, const Eigen::Vector3d& position,
                 double radius, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_SPHERE(const std::string& drawingChannel, double posX, double posY, double posZ,
                 double radius, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_POLYLINE(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const std::vector<Eigen::Vector3d>& points, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_POLYLINE(const std::string& drawingChannel, const std::vector<Eigen::Vector3d>& points,
                   const Eigen::Vector4d& colorRGBA)
{
}


WEAK void DRAW_TEXT(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, const std::string& text,
               double fontSize, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_TEXT(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_TEXT(const std::string& drawingChannel, double posX, double posY, double posZ,
               double rotW, double rotX, double rotY, double rotZ,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_TEXT(const std::string& drawingChannel, double posX, double posY, double posZ,
               const std::string& text, double fontSize, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_LINE(const std::string& drawingChannel, const Eigen::Vector3d& from, const Eigen::Vector3d& to,
               const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_CYLINDER(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size,
                   const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_CYLINDER(const std::string& drawingChannel, const Eigen::Vector3d& position,
                   const Eigen::Vector3d& size, const Eigen::Vector4d& colorRGBA)
{
}

WEAK void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation, const Eigen::Vector3d& size)
{
}

WEAK void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position,
               const Eigen::Quaterniond& orientation)
{
}

WEAK void DRAW_AXES(const std::string& drawingChannel, const Eigen::Vector3d& position)
{
}

WEAK void DRAW_AABB(const std::string& drawingChannel, Eigen::AlignedBox3d box,
               const Eigen::Vector4d& colorRGBA)
{
}

WEAK void PLOT_2D(const std::string& drawingChannel, const Eigen::Vector2d& dataPoint)
{
}

WEAK void CLEAR_PLOT(const std::string& plotName)
{
}

WEAK void REMOVE_DRAWING(const std::string& drawingChannel)
{
}

WEAK void CLEAR_DRAWING(const std::string& drawingChannel)
{
}

WEAK void FLUSH_DRAWINGS()
{
}

WEAK std::vector<std::string> GET_DECLARED_CHANNELS()
{
    std::vector<std::string> outChannels;
    return outChannels;
}

}
