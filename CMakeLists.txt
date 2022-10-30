cmake_minimum_required(VERSION 3.22)
project(pproxy)
set(CMAKE_CXX_STANDARD 14)

include_directories(socket)

add_subdirectory(socket)
add_subdirectory(proxy)

add_executable(pproxy main.cpp)

target_include_directories(pproxy PRIVATE socket proxy)

target_link_libraries(pproxy socket proxy)