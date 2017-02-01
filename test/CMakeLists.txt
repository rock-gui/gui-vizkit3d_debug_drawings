add_definitions(-DENABLE_DEBUG_DRAWINGS)
rock_executable(draw_test draw_test.cpp
    DEPS 
        vizkit3dDebugDrawings
    DEPS_PKGCONFIG 
        base-types 
)