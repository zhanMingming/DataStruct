cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

project(demo)

find_package(GTEST REQUIRED)

INCLUDE_DIRECTORIES(../Util  /usr/local/include/  /usr/include/)
add_executable(${PROJECT_NAME} TestArena.cpp  Arena.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
