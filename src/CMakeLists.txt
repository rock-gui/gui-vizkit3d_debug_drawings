rock_library(vizkit3dDebugDrawings
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(vizkit3dDebugDrawings_bin Main.cpp
    DEPS vizkit3dDebugDrawings)

