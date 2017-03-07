#include <boost/test/unit_test.hpp>
#define private public //HACK to compare members of DrawSphereCommand
#include <vizkit3d_debug_drawings/commands/primitives/DrawSphereCommand.h>
#include <base/Eigen.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>

using namespace vizkit3dDebugDrawings;
using namespace boost;
BOOST_AUTO_TEST_CASE(serializaton_test_1)
{
    DrawSphereCommand cmd("test123", base::Vector3d(1,42,0), 0.42, base::Vector4d(1, 0, 0, 1));
    
    std::vector<char> buffer;
    
    iostreams::back_insert_device<std::vector<char>> sink{buffer};
    iostreams::stream<iostreams::back_insert_device<std::vector<char>>> os{sink};
    archive::binary_oarchive oa(os);
    
    oa << cmd;
    os.flush(); //don't forget to flush, otherwise small data types might not be written immediately
    
    BOOST_CHECK(buffer.size() > 0);
    
    iostreams::array_source source{buffer.data(), buffer.size()};
    iostreams::stream<iostreams::array_source> is{source};
    archive::binary_iarchive ia(is);
    
    DrawSphereCommand cmd2;
    ia >> cmd2;
    
    BOOST_CHECK(cmd.getDrawingName() == cmd2.getDrawingName());
    BOOST_CHECK(cmd.radius == cmd2.radius);
    BOOST_CHECK(cmd.radius == cmd2.radius);
    BOOST_CHECK(cmd.position.x() == cmd2.position.x());
    BOOST_CHECK(cmd.position.y() == cmd2.position.y());
    BOOST_CHECK(cmd.position.z() == cmd2.position.z());
    BOOST_CHECK(cmd.colorRGBA[0] == cmd2.colorRGBA[0]);
    BOOST_CHECK(cmd.colorRGBA[1] == cmd2.colorRGBA[1]);
    BOOST_CHECK(cmd.colorRGBA[2] == cmd2.colorRGBA[2]);
    BOOST_CHECK(cmd.colorRGBA[3] == cmd2.colorRGBA[3]);
}