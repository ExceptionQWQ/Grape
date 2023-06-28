cmake_minimum_required(VERSION 3.14)

project(grape)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. SRC_LISTS)

add_executable(grape ${SRC_LISTS})

target_link_libraries(grape -lwiringPi -pthread)
