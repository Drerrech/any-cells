cmake_minimum_required(VERSION 3.14)
project(SFML_Cellular)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(SOURCE_FILES main.cpp Display.cpp Display.hpp cells.cpp cells.h)
add_executable(SFML_Cellular ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SFML_Cellular sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
