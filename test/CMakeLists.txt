add_definitions(-DENABLE_DEBUG_DRAWINGS)
rock_executable(draw_test draw_test.cpp
    DEPS 
        vizkit3d_debug_drawings
    DEPS_PKGCONFIG 
        base-types 
)