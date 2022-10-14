cmake_minimum_required(VERSION 3.5)
project(sircon)

set(CMAKE_CXX_FLAGS -O2)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        main.cpp
        ./include/clipp.h
        ./include/ConfigArgs.cpp
        ./include/ConfigArgs.h
        ./include/Graph.cpp
        ./include/Graph.h
        ./include/clipp.h
        Functions.cpp
        Functions.h
        )