cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

project(TestSkipList)

find_package(GTEST REQUIRED)

INCLUDE_DIRECTORIES(../Util  ../Arena /usr/local/include/  /usr/include/)
add_executable(${PROJECT_NAME} TestSkipList.cpp  ../Arena/Arena.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
