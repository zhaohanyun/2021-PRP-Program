cmake_minimum_required(VERSION 3.12)
project(flow_test)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR D:\\opencv\\opencv\\build\\mingw-build2)
set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

#include_directories("D:\\Program Files (x86)\\opencv\\opencv\\mingw-build\\install\\include")
include_directories(D:/opencv/opencv/build/include/opencv)
include_directories(D:/opencv/opencv/build/include/opencv2)
add_executable(flow_test main.cpp)

#SET(OpenCV_LIB D:/opencv/opencv/build/x64/vc14/lib)
#target_include_directories(flow_test PUBLIC D:/opencv/opencv/build/mingw-build/lib)
target_link_libraries(flow_test ${OpenCV_LIB})

