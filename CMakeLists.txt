cmake_minimum_required(VERSION 3.12)
project(tp_1_sem)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -DCMAKE_OSX_ARCHITECTURES")

#set(PROJECT_SOURCE_FILES project/src/main.cpp project/src/CListGraph.cpp project/src/CMatrixGraph.cpp
#        project/src/CArcGraph.cpp project/src/CSetGraph.cpp project/src/GraphGen.cpp project/src/Generator.cpp)

set(PROJECT_SOURCE_FILES project/src/3.cpp)

include_directories(project/include)

add_executable(tp_1_sem ${PROJECT_SOURCE_FILES})
