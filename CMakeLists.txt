cmake_minimum_required(VERSION 3.26)
project(hrd)

set(CMAKE_CXX_STANDARD 17)
include_directories(./easyx/include)
link_directories(./easyx/lib64)
link_libraries(libeasyx.a)

add_executable(hrd0 hrd0.cpp)
target_link_libraries(hrd0 winmm)