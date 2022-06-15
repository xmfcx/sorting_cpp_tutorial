cmake_minimum_required(VERSION 3.22)
project(sorting_cpp)

set(CMAKE_CXX_STANDARD 17)

find_package(TBB REQUIRED)

add_executable(sorting_cpp main.cpp)

# link libtbb
target_link_libraries(sorting_cpp TBB::tbb)