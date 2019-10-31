cmake_minimum_required(VERSION 3.15)
project(cpplab)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 14)

add_executable(cpplab element.cpp main.cpp)
target_link_libraries(cpplab ${GTEST_LIBRARIES} pthread)