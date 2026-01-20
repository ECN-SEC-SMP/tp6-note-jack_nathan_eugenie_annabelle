
cmake_minimum_required(VERSION 3.0)
project(CPP_TP6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(MAKE_DIRECTORY output) # Create directory for outputs

set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gamehandler.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/_.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_definitions(PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(CPP_TP6 ${sources})