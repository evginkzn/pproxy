cmake_minimum_required(VERSION 3.22)

link_libraries(socket)
add_library(proxy STATIC Proxy.cpp)
