cmake_minimum_required (VERSION 3.0.0)

SET(CMAKE_BUILD_TYPE "Debug")  # 定义编译类型
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -pthread") # 定义Debug编译参数
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -pthread") # 定义Release编译参数
SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -Wall -pthread")

project (MyRpc)

add_subdirectory (src)
