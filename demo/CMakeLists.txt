cmake_minimum_required(VERSION 3.22)

add_executable(demo demo.cpp)

set_property(TARGET demo PROPERTY CXX_STANDARD 17)

target_link_libraries(demo PUBLIC geohash)
