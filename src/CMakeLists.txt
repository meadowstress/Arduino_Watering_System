cmake_minimum_required(VERSION 3.0)

project(Pump_Control)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


add_executable(
    runTest_unit
    unit_test.cpp
    mock_arduino.cpp
    time.cpp
    PS_func.cpp
)

add_executable(
    Arduino_PS
    Arduino_PS.cpp
    PS_func.cpp
    mock_arduino.cpp
    time.cpp
)

add_executable(
    runTest_mock
    test_mocks.cpp
    mock_arduino.cpp
)



# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(runTest_mock ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTest_unit ${GTEST_LIBRARIES} pthread) 

 
