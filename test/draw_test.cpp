#include <iostream>
#include <vizkit3d_debug_drawings/DebugDrawing.h>
#include <chrono>
#include <thread>
#include <base/Eigen.hpp>
#include <random>

int main()
{
    CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    Eigen::Vector4d color(1, 0, 0, 1);
    DRAW_SPHERE("sphere", -2, 1, 1, .5, color);
    DRAW_SPHERE("sphere", base::Vector3d(-2, 1, 0), .5, color);
    
    base::Vector3d ringPos(1, 0, 0);
    base::Quaterniond ringRot(Eigen::AngleAxisd(0.42, base::Vector3d::UnitX()));
    base::Vector4d ringCol(1, 1, 0, 0.5);
    DRAW_RING("ring", ringPos, ringRot, 1, 0.1, 0.05, ringCol);
    
    ringRot = base::Quaterniond::Identity();
    ringPos << 3, 1, 0;
    DRAW_RING("ring", ringPos, ringRot, 1, 0.1, 0.05, ringCol);
    ringPos.z() += 0.2;
    DRAW_RING("ring", ringPos, 1, 0.1, 0.05, ringCol);
     
    base::Vector3d pos(1, 2, 3);
    DRAW_TEXT("testText", pos, "Work, work.", 0.3, color);
    base::Quaterniond rot(Eigen::AngleAxisd(1.57, base::Vector3d::UnitX()));
    DRAW_TEXT("testText", pos, rot, "yes, me lord.", 0.3, color);
    rot = Eigen::AngleAxisd(M_PI, base::Vector3d::UnitX());
    DRAW_TEXT("testText", pos, rot, "Job's done!", 0.3, color);
    
    
    base::Vector3d wireframePos(0, 2, 0);
    base::Quaterniond wireframeRot(Eigen::AngleAxisd(0.5, base::Vector3d::UnitY()));
    base::Vector3d wireframeSize(0.5, 1, 2);
    base::Vector4d wireframeColor(0, 0, 1, 1);
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeRot, wireframeSize, wireframeColor);
    wireframePos << 0, 3, 1;
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, base::Quaterniond::Identity(), wireframeSize, wireframeColor);
    wireframePos.z() += 2.2;
    DRAW_WIREFRAME_BOX("wireframeBox", wireframePos, wireframeSize, wireframeColor);
    
    
    base::Vector3d arrowPos(-1, -1, -1);
    base::Vector3d arrowSize(1, 1, 1);
    base::Vector4d arrowColor(1, 1, 1, 1);    
    DRAW_ARROW("arrow", arrowPos, arrowSize, arrowColor);
    base::Quaterniond arrowRot(Eigen::AngleAxisd(0.7, base::Vector3d::UnitY()));
    arrowColor.x() -= 0.3;
    DRAW_ARROW("arrow", arrowPos, arrowRot, arrowSize, arrowColor);
    
    
// 
// 
//     double w = 0.017;
//     std::uniform_real_distribution<double> colorRnd(0, 1);
    while(true)
    {
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
