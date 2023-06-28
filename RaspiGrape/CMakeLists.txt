cmake_minimum_required(VERSION 3.14)

project(grape)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

aux_source_directory(. SRC_LISTS)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(grape ${SRC_LISTS})

target_link_libraries(grape ${OpenCV_LIBS} -lwiringPi -pthread)
