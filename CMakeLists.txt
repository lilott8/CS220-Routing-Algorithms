cmake_minimum_required(VERSION 2.8.4)
project(CS220_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_subdirectory(Algorithms)
add_subdirectory(Maps)
add_subdirectory(DataStructures)

add_executable(CS220_Project ${SOURCE_FILES})

target_link_libraries(CS220_Project LEE)

target_link_libraries(CS220_Project DS)

target_link_libraries(CS220_Project MAPS)

target_link_libraries(CS220_Project HADLOCK)