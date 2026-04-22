cmake_minimum_required(VERSION 3.22)
project(MovingBallSimulation)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES ON) 
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(MovingBallSimulation src/main.cpp)

target_link_libraries(MovingBallSimulation PRIVATE SFML::Graphics SFML::Window SFML::System)

# TODO: To implement FetchContent later for automated dependency management