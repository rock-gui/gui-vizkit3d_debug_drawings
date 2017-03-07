#include <iostream>
#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <chrono>
#include <thread>
#include <base/Eigen.hpp>
#include <random>

int main()
{
    Eigen::Vector4d color(1, 0, 0, 1);
    DRAW_RING("test", 1, 1, 1, 1, 1, 0, 0, 1, 0.05, 0.01, color);
    
    DRAW_WIREFRAME_BOX("box", 0, 0, 1, 1, 0.3, 0.2, 0, 0.5, 0.5, 0.3, color);
    DRAW_WIREFRAME_BOX("box", 0, 0, 1, 0.2, 0.2, 0.2, color);
    color[2] = 0.5;
    DRAW_WIREFRAME_BOX("box", 0, 0, 1, color);
    
    double x = 0;
    double y = 0;
    double z = 0;
    std::vector<base::Vector3d> points;
    std::default_random_engine rndEngine;
    std::uniform_real_distribution<double> rnd(0.001, 0.1);
    for(int i = 0; i < 100; ++i)
    {
        points.emplace_back(x, y, z);
        x += rnd(rndEngine);
        y += rnd(rndEngine);
        z -= rnd(rndEngine);
    }

    color[1] = 1;
    DRAW_POLYLINE("polyLine", 2, 2, 2, points, color);
    
    base::Vector3d pos(1, 2, 3);
    DRAW_TEXT("testText", pos, "Work, work.", 0.3, color);
    base::Quaterniond rot(Eigen::AngleAxisd(1.57, base::Vector3d::UnitX()));
    DRAW_TEXT("testText", pos, rot, "yes, me lord.", 0.3, color);
    rot = Eigen::AngleAxisd(M_PI, base::Vector3d::UnitX());
    DRAW_TEXT("testText", pos, rot, "Job's done!", 0.3, color);


    double w = 0.017;
    std::uniform_real_distribution<double> colorRnd(0, 1);
    while(true)
    {
        Eigen::Vector4d color(colorRnd(rndEngine), colorRnd(rndEngine), colorRnd(rndEngine), 1);
        CLEAR_DRAWING("arrrr");
        Eigen::Quaterniond rot(Eigen::AngleAxisd(w, Eigen::Vector3d::UnitY()));
        DRAW_ARROW("arrrr", -1, -1, 0, rot.w(), rot.x(), rot.y(), rot.z(), 0.4,
                   0.8, 0.6, color);
        w += 0.07;

        DRAW_SPHERE("sphere", -2, 1, 1, 1, color);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        REMOVE_DRAWING("sphere"); //NOTE <-- this is not a good use of REMOVE_DRAWING it is only here to test threading issues
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
