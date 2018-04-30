#include <boost/test/unit_test.hpp>
#define private public //HACK to compare members of DrawSphereCommand
#include <vizkit3d_debug_drawings/commands/primitives/DrawSphereCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawArrowCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawCylinderCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawPolyLineCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawRingCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawTextCommand.h>
#include <vizkit3d_debug_drawings/commands/primitives/DrawWireframeBoxCommand.h>
#include <vizkit3d_debug_drawings/commands/ClearDrawingCommand.h>
#include <vizkit3d_debug_drawings/commands/RemoveDrawingCommand.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <vizkit3d_debug_drawings/DebugDrawingColors.h>
#include <boost/serialization/export.hpp>

using namespace vizkit3dDebugDrawings;
using namespace boost;


template <class T>
T serializeAndDeserialize(const T& data)
{
    std::vector<char> buffer;
    
    iostreams::back_insert_device<std::vector<char>> sink{buffer};
    iostreams::stream<iostreams::back_insert_device<std::vector<char>>> os{sink};
    archive::binary_oarchive oa(os);
    
    oa << data;
    os.close();
    
    BOOST_CHECK(buffer.size() > 0);
    
    iostreams::array_source source{buffer.data(), buffer.size()};
    iostreams::stream<iostreams::array_source> is{source};
    archive::binary_iarchive ia(is);
    T data2;
    ia >> data2;
    return data2;
}

void compare(const Eigen::Vector3d& a, const Eigen::Vector3d& b)
{
    BOOST_CHECK(a.x() == b.x());
    BOOST_CHECK(a.y() == b.y());
    BOOST_CHECK(a.z() == b.z());
}

void compare(const Eigen::Vector4d& a, const Eigen::Vector4d& b)
{
    for(int i = 0; i < 4; ++i)
        BOOST_CHECK(a[i] == b[i]);
}

void compare(const Eigen::Quaterniond& a, const Eigen::Quaterniond& b)
{
    for(int i = 0; i < 4; ++i)
        BOOST_CHECK(a.vec()[i] == b.vec()[i]);    
}

void compare(double a, double b)
{
    BOOST_CHECK(a == b);
}

void compare(const std::string& a, const std::string& b)
{
    BOOST_CHECK(a == b);
}

template <class T>
void compare(const std::vector<T>& a, const std::vector<T>& b)
{
    BOOST_CHECK(a.size() == b.size());
    for(size_t i = 0; i < a.size(); ++i)
    {
        compare(a[i], b[i]);
    }
}

BOOST_CLASS_EXPORT(vizkit3dDebugDrawings::DrawSphereCommand);

BOOST_AUTO_TEST_CASE(serialize_base_test)
{
    Command* cmd = new DrawSphereCommand("test123", Eigen::Vector3d(1,42,0), 0.42, Eigen::Vector4d(1, 0, 0, 1));
    
    std::vector<char> buffer;
    
    iostreams::back_insert_device<std::vector<char>> sink{buffer};
    iostreams::stream<iostreams::back_insert_device<std::vector<char>>> os{sink};
    archive::binary_oarchive oa(os);
    
    oa << cmd;
    os.close();
    
    BOOST_CHECK(buffer.size() > 0);
    
    iostreams::array_source source{buffer.data(), buffer.size()};
    iostreams::stream<iostreams::array_source> is{source};
    archive::binary_iarchive ia(is);

    Command* cmd2;
    ia >> cmd2;
    
    BOOST_CHECK(dynamic_cast<DrawSphereCommand*>(cmd2) != nullptr);
    
    
}



BOOST_AUTO_TEST_CASE(sphere_cmd_test)
{
    DrawSphereCommand a("test123", Eigen::Vector3d(1,42,0), 0.42, Eigen::Vector4d(1, 0, 0, 1));
    DrawSphereCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.radius, b.radius);
    compare(a.getDrawingName(), b.getDrawingName());
}

BOOST_AUTO_TEST_CASE(arrow_cmd_test)
{
    DrawArrowCommand a("lala", Eigen::Vector3d(1,42,0), Eigen::Quaterniond(1,1,1,1), Eigen::Vector3d(0.1, 0.2, 0.3),
                       vizkit3dDebugDrawings::Color::red);
    DrawArrowCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.getDrawingName(), b.getDrawingName());
    compare(a.orientation, b.orientation);
    compare(a.scale, b.scale);
}

BOOST_AUTO_TEST_CASE(cylinder_cmd_test)
{
    DrawCylinderCommand a("lala", Eigen::Vector3d(1,42,0), Eigen::Quaterniond(1,1,1,1), Eigen::Vector3d(0.1, 0.2, 0.3),
                       vizkit3dDebugDrawings::Color::red);
    DrawCylinderCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.getDrawingName(), b.getDrawingName());
    compare(a.orientation, b.orientation);
    compare(a.size, b.size);
}


BOOST_AUTO_TEST_CASE(polyline_cmd_test)
{
    DrawPolyLineCommand a("polypp", Eigen::Vector3d(1,42,0.23), vizkit3dDebugDrawings::Color::green_ncs);
    
    a.getPoints().emplace_back(0, 1, 2);
    a.getPoints().emplace_back(0.03, 1, 22);
    a.getPoints().emplace_back(-0.230, 12, 42);
    a.getPoints().emplace_back(0, 0, -2.2242);
    
    DrawPolyLineCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.getDrawingName(), b.getDrawingName());
    compare(a.getPoints(), b.getPoints());
}

BOOST_AUTO_TEST_CASE(ring_cmd_test)
{
    DrawRingCommand a("ringaa", Eigen::Vector3d(1,422,0), Eigen::Quaterniond(1,0,09.4,1), 0.3, 1.42, 1.22, vizkit3dDebugDrawings::Color::neon_carrot);
    DrawRingCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.getDrawingName(), b.getDrawingName());
    compare(a.orientation, b.orientation);
    compare(a.height, b.height);
    compare(a.thickness, b.thickness);
    compare(a.radius, b.radius);
}

BOOST_AUTO_TEST_CASE(text_cmd_test)
{
    DrawTextCommand a("qqq", Eigen::Vector3d(1,422,0), Eigen::Quaterniond(1,0,09.4,1), "bla bla bu", 42.042, vizkit3dDebugDrawings::Color::yale_blue);
    DrawTextCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.getDrawingName(), b.getDrawingName());
    compare(a.orientation, b.orientation);
    compare(a.fontSize, b.fontSize);
    compare(a.text, b.text);
}

BOOST_AUTO_TEST_CASE(wireframe_cmd_test)
{
    DrawWireframeBoxCommand a("law", Eigen::Vector3d(12,422,0), Eigen::Quaterniond(11,0,09.4,1), Eigen::Vector3d(1,2,3), vizkit3dDebugDrawings::Color::zaffre);
    DrawWireframeBoxCommand b = serializeAndDeserialize(a);
    compare(a.colorRGBA, b.colorRGBA);
    compare(a.position, b.position);
    compare(a.getDrawingName(), b.getDrawingName());
    compare(a.orientation, b.orientation);
    compare(a.size, b.size);
}

BOOST_AUTO_TEST_CASE(clear_cmd_test)
{
    ClearDrawingCommand a("asdsadqweqwe");
    ClearDrawingCommand b = serializeAndDeserialize(a);
    compare(a.getDrawingName(), b.getDrawingName());
}

BOOST_AUTO_TEST_CASE(remove_cmd_test)
{
    RemoveDrawingCommand a("qwqewqeqwe565467dgfc");
    RemoveDrawingCommand b = serializeAndDeserialize(a);
    compare(a.getDrawingName(), b.getDrawingName());
}



