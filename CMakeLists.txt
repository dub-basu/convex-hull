cmake_minimum_required( VERSION 3.0 )

project( convex-hull )

# flags

# include
include_directories( ./src )

# target
add_executable(convex-hull
                ./src/main.cpp
                ./src/primitives.cpp
                ./src/GrahamScan.cpp
                ./src/JarvisMarch.cpp
            )
