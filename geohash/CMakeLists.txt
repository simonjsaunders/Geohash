cmake_minimum_required(VERSION 3.22)

add_library(geohash STATIC geohash.cpp)

set_property(TARGET geohash PROPERTY CXX_STANDARD 17)

target_include_directories(geohash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})