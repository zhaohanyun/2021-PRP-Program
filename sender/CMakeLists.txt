cmake_minimum_required(VERSION 3.17)
project(sender)

set(CMAKE_CXX_STANDARD 14)


find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})


add_executable(sender sender_zhy.cpp)

target_link_libraries(sender ${JSONCPP_LIBRARIES})