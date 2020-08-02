cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 11)

project(Arduino_Watering_System VERSION 12.2.0)


# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message("GTEST_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}")

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

include_directories(include mock)

add_library(
    test_library

    PS_func.cpp
    mytime.cpp
    mock/mock_arduino.cpp
)

add_executable(
    Arduino_PS
    Arduino_PS.cpp
)

target_link_libraries(Arduino_PS test_library)

add_subdirectory(test)