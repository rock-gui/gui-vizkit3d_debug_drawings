#include <iostream>
#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <vizkit3d_debug_drawings/DebugDrawingColors.h>
#include <chrono>
#include <thread>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <base/samples/RigidBodyState.hpp>
#include <random>


int main()
{
    CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    
    //draw something to test buffering before configuration
    DRAW_CYLINDER("cylinder", Eigen::Vector3d(3, 3, 2), Eigen::Vector3d(1,1,1),
                  vizkit3dDebugDrawings::Color::android_green);

    Eigen::Vector4d color(1, 0, 0, 1);
    DRAW_SPHERE("sphere", -2, 1, 1, .5, color);
    DRAW_SPHERE("sphere", Eigen::Vector3d(-2, 1, 0), .5, color);
    
    Eigen::Vector3d ringPos(1, 0, 0);
    Eigen::Quaterniond ringRot(Eigen::AngleAxisd(0.42, Eigen::Vector3d::UnitX()));
    Eigen::Vector4d ringCol(1, 1, 0, 0.5);
    DRAW_RING("ring", ringPos, ringRot, 1, 0.1, 0.05, ringCol);
    
    ringRot = Eigen::Quaterniond::Identity();
    ringPos << 3, 1, 0;
    DRAW_RING("ring", ringPos, ringRot, 1, 0.1, 0.05, ringCol);
    ringPos.z() += 0.2;
    DRAW_RING("ring", ringPos, 1, 0.1, 0.05, ringCol);
     
    Eigen::Vector3d pos(1, 2, 3);
    DRAW_TEXT("testText", pos, "Work, work.", 0.3, color);
    Eigen::Quaterniond rot(Eigen::AngleAxisd(1.57, Eigen::Vector3d::UnitX()));
    DRAW_TEXT("testText", pos, rot, "yes, me lord.", 0.3, color);
    rot = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX());
    DRAW_TEXT("testText", pos, rot, "Job's done!", 0.3, color);
    
    
    DRAW_AXES("axes1", Eigen::Vector3d(2,0,1));
    DRAW_AXES("axes1", Eigen::Vector3d(4,0,1), Eigen::Quaterniond::Identity(), Eigen::Vector3d(2,2,2));
    DRAW_AXES("axes1", Eigen::Vector3d(3,0,1), Eigen::Quaterniond(Eigen::AngleAxisd(1.57, Eigen::Vector3d::UnitX())));
    
    
    
    Eigen::Vector3d wireframePos(0, 2, 0);
    Eigen::Quaterniond wireframeRot(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitY()));
    Eigen::Vector3d wireframeSize(0.5, 1, 2);
    Eigen::Vector4d wireframeColor(0, 0, 1, 1);
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeRot, wireframeSize, wireframeColor);
    wireframePos << 0, 3, 1;
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, Eigen::Quaterniond::Identity(), wireframeSize, wireframeColor);
    wireframePos.z() += 2.2;
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeSize, wireframeColor);
    wireframePos << 0, 0, 0;
    wireframeSize << 0.5, 0.5, 0.5;
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeSize, wireframeColor);
    
    
    Eigen::Vector3d arrowPos(-1, -1, -1);
    Eigen::Vector3d arrowSize(1, 1, 1);
    Eigen::Vector4d arrowColor(1, 1, 1, 1);    
    DRAW_ARROW("arrow", arrowPos, arrowSize, arrowColor);
    Eigen::Quaterniond arrowRot(Eigen::AngleAxisd(0.7, Eigen::Vector3d::UnitY()));
    arrowColor.x() -= 0.3;
    DRAW_ARROW("arrow", arrowPos, arrowRot, arrowSize, arrowColor);
    
    
    Eigen::Vector3d linePos(-1, 0, 0);
    Eigen::Vector4d lineColor(1, 0, 0, 1);    
    std::vector<Eigen::Vector3d> points;
    points.emplace_back(0, 0, 0);
    points.emplace_back(0, 0, 2);
    points.emplace_back(2, 0, 2);
    points.emplace_back(2, 2, 2);
    DRAW_POLYLINE("polyLine", linePos, points, lineColor);
    DRAW_POLYLINE("polyLine2", points, lineColor);
    DRAW_LINE("line", Eigen::Vector3d(-1, -1, -1), Eigen::Vector3d(0, 1, 2), vizkit3dDebugDrawings::Color::cyan);
    

    Eigen::Vector3d min, max;
    min << -1, -1, -1;
    max << 1, 1, 1;
    Eigen::AlignedBox3d boundingBox(min, max);
    DRAW_AABB("AABB", boundingBox, vizkit3dDebugDrawings::Color::alloy_orange);
    

    
    double x = 0;
    size_t i = 0;
    while(true)
    {
        x += 0.1;
        PLOT_2D("sin", {x,std::sin(x)});
        PLOT_2D("cos", {x, std::cos(x)});
        PLOT_2D("tan", {x, std::tan(x)});
        PLOT_2D("atan", {x, std::atan(x)});
        PLOT_2D("x", {x, x});
        
        if(i > 100)
        {
            CLEAR_PLOT("x");
            i = 0;
        }
        ++i;
        
        Eigen::Vector3d blinkPos(-3, -3, -3);
        DRAW_SPHERE("removeTest", blinkPos, 1, vizkit3dDebugDrawings::Color::air_force_blue_raf);
        DRAW_SPHERE("remvoeTest2", Eigen::Vector3d(-4, -4, -4), 0.8, vizkit3dDebugDrawings::Color::cadmium_orange);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        REMOVE_DRAWING("removeTest");
        CLEAR_DRAWING("remvoeTest2");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
//         Eigen::Vector4d color(colorRnd(rndEngine), colorRnd(rndEngine), colorRnd(rndEngine), 1);
//         CLEAR_DRAWING("arrrr");
//         Eigen::Quaterniond rot(Eigen::AngleAxisd(w, Eigen::Vector3d::UnitY()));
//         DRAW_ARROW("arrrr", -1, -1, 0, rot.w(), rot.x(), rot.y(), rot.z(), 0.4,
//                    0.8, 0.6, color);
//         w += 0.07;
// 
//         DRAW_SPHERE("sphere", -2, 1, 1, 1, color);
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//         REMOVE_DRAWING("sphere"); //NOTE <-- this is not a good use of REMOVE_DRAWING it is only here to test threading issues
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
