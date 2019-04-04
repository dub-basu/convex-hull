cmake_minimum_required( VERSION 3.0 )

project( convex-hull )

find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

# flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# include
include_directories( ./src )

# target
add_executable(convex-hull
                ./src/main.cpp
                ./src/primitives.cpp
                ./src/GrahamScan.cpp
                ./src/JarvisMarch.cpp
                ./src/Graphix.cpp
                ./src/ConvexHullGraphix.cpp
            )

target_link_libraries(convex-hull glfw ${OPENGL_LIBRARY})
