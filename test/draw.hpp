#include <iostream>
#include <vizkit3d_debug_drawings/DebugDrawing.hpp>
#include <vizkit3d_debug_drawings/DebugDrawingColors.hpp>
#include <chrono>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <random>
#include <thread>

V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("cylinder");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("sphere");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("ring");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("testText");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("axes1");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("wireframeBox");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("polyLine");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("polyLine2");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("line");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("Complex");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("removeTest");
V3DD_DECLARE_DEBUG_DRAWING_CHANNEL("removeTest2");

void draw()
{    
    //draw something to test buffering before configuration
    V3DD::DRAW_CYLINDER("cylinder", Eigen::Vector3d(3, 3, 2), Eigen::Vector3d(1,1,1),
                  V3DD::Color::android_green);

    Eigen::Vector4d color(1, 0, 0, 1);
    V3DD::DRAW_SPHERE("sphere", -2, 1, 1, .5, color);
    V3DD::DRAW_SPHERE("sphere", Eigen::Vector3d(-2, 1, 0), .5, color);
    
    Eigen::Vector3d ringPos(1, 0, 0);
    Eigen::Quaterniond ringRot(Eigen::AngleAxisd(0.42, Eigen::Vector3d::UnitX()));
    Eigen::Vector4d ringCol(1, 1, 0, 0.5);
    V3DD::DRAW_RING("ring", ringPos, ringRot, 1, 0.1, 0.05, ringCol);
    
    ringRot = Eigen::Quaterniond::Identity();
    ringPos << 3, 1, 0;
    V3DD::DRAW_RING("ring", ringPos, ringRot, 1, 0.1, 0.05, ringCol);
    ringPos.z() += 0.2;
    V3DD::DRAW_RING("ring", ringPos, 1, 0.1, 0.05, ringCol);
     
    Eigen::Vector3d pos(1, 2, 3);
    V3DD::DRAW_TEXT("testText", pos, "Work, work.", 0.3, color);
    Eigen::Quaterniond rot(Eigen::AngleAxisd(1.57, Eigen::Vector3d::UnitX()));
    V3DD::DRAW_TEXT("testText", pos, rot, "yes, me lord.", 0.3, color);
    rot = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitX());
    V3DD::DRAW_TEXT("testText", pos, rot, "Job's done!", 0.3, color);
    
    
    V3DD::DRAW_AXES("axes1", Eigen::Vector3d(2,0,1));
    V3DD::DRAW_AXES("axes1", Eigen::Vector3d(4,0,1), Eigen::Quaterniond::Identity(), Eigen::Vector3d(2,2,2));
    V3DD::DRAW_AXES("axes1", Eigen::Vector3d(3,0,1), Eigen::Quaterniond(Eigen::AngleAxisd(1.57, Eigen::Vector3d::UnitX())));
    
    
    
    Eigen::Vector3d wireframePos(0, 2, 0);
    Eigen::Quaterniond wireframeRot(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitY()));
    Eigen::Vector3d wireframeSize(0.5, 1, 2);
    Eigen::Vector4d wireframeColor(0, 0, 1, 1);
    V3DD::DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeRot, wireframeSize, wireframeColor);
    wireframePos << 0, 3, 1;
    V3DD::DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, Eigen::Quaterniond::Identity(), wireframeSize, wireframeColor);
    wireframePos.z() += 2.2;
    V3DD::DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeSize, wireframeColor);
    wireframePos << 0, 0, 0;
    wireframeSize << 0.5, 0.5, 0.5;
    V3DD::DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeSize, wireframeColor);
    
    
    Eigen::Vector3d arrowPos(-1, -1, -1);
    Eigen::Vector3d arrowSize(1, 1, 1);
    Eigen::Vector4d arrowColor(1, 1, 1, 1);    
    V3DD::DRAW_ARROW("arrow", arrowPos, arrowSize, arrowColor);
    Eigen::Quaterniond arrowRot(Eigen::AngleAxisd(0.7, Eigen::Vector3d::UnitY()));
    arrowColor.x() -= 0.3;
    V3DD::DRAW_ARROW("arrow", arrowPos, arrowRot, arrowSize, arrowColor);
    
    
    Eigen::Vector3d linePos(-1, 0, 0);
    Eigen::Vector4d lineColor(1, 0, 0, 1);    
    std::vector<Eigen::Vector3d> points;
    points.emplace_back(0, 0, 0);
    points.emplace_back(0, 0, 2);
    points.emplace_back(2, 0, 2);
    points.emplace_back(2, 2, 2);
    V3DD::DRAW_POLYLINE("polyLine", linePos, points, lineColor);
    V3DD::DRAW_POLYLINE("polyLine2", points, lineColor);
    V3DD::DRAW_LINE("line", Eigen::Vector3d(-1, -1, -1), Eigen::Vector3d(0, 1, 2), V3DD::Color::cyan);
    


    V3DD::COMPLEX_DRAWING([]()
    {
        Eigen::Vector3d min, max;
        min << -1, -1, -1;
        max << 1, 1, 1;
        Eigen::AlignedBox3d boundingBox(min, max);
        V3DD::DRAW_AABB("Complex", boundingBox, V3DD::Color::alloy_orange);
         V3DD::DRAW_SPHERE("Complex", -7, 1, 1, 1, V3DD::Color::magenta);
    });
    

    double x = 0;
    size_t i = 0;
    while(true)
    {
        x += 0.1;
        V3DD::PLOT_2D("sin", Eigen::Vector2d{x,std::sin(x)});
        V3DD::PLOT_2D("cos", Eigen::Vector2d{x, std::cos(x)});
        V3DD::PLOT_2D("tan", Eigen::Vector2d{x, std::tan(x)});
        V3DD::PLOT_2D("atan", Eigen::Vector2d{x, std::atan(x)});
        V3DD::PLOT_2D("x", Eigen::Vector2d{x, x});
        
        if(i > 100)
        {
            V3DD::CLEAR_PLOT("x");
            i = 0;
        }
        ++i;
        
        Eigen::Vector3d blinkPos(-3, -3, -3);
        V3DD::DRAW_SPHERE("removeTest", blinkPos, 1, V3DD::Color::air_force_blue_raf);
        V3DD::DRAW_SPHERE("remvoeTest2", Eigen::Vector3d(-4, -4, -4), 0.8, V3DD::Color::cadmium_orange);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        V3DD::REMOVE_DRAWING("removeTest");
        V3DD::CLEAR_DRAWING("remvoeTest2");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}
