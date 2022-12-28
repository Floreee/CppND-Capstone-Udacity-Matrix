cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

project(UdacityMatrix)

file(GLOB project_SRCS src/*.cpp)
add_executable(UdacityMatrix ${project_SRCS})
