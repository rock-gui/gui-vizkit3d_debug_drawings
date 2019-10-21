#include <vizkit3d_debug_drawings/DebugDrawing.hpp>
#include "draw.hpp"
#include <iostream>



int main()
{
    V3DD::CONFIGURE_DEBUG_DRAWINGS_STANDALONE();
    
    auto channels = V3DD::GET_DECLARED_CHANNELS();
    
    std::cout << "DECLARED CHANNELS:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    for(const std::string& channel : channels)
    {
        std::cout << channel << std::endl;
    }
    std::cout << "----------------------------------------------------" << std::endl;
    
    draw();
    return 0;
}
