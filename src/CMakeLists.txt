cmake_minimum_required(VERSION 3.0)

project(Pump_Control)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


add_executable(
    Arduino_PS
    Arduino_PS.cpp
    PS_func.cpp
    mock/mock_arduino.cpp
    time.cpp
)

add_executable(
    runTest_all
    test/test_main_all.cpp
    mock/mock_arduino.cpp
    time.cpp
    PS_func.cpp
)

add_executable(
    runTest_Time
    test/test_main_Time.cpp
    mock/mock_arduino.cpp
    time.cpp
    PS_func.cpp
)

add_executable(
    runTest_WaterSystem
    test/test_main_WaterSystem.cpp
    mock/mock_arduino.cpp
    time.cpp
    PS_func.cpp
)

add_executable(
    runTest_Mocks
    test/test_main_Mocks.cpp
    mock/mock_arduino.cpp
    time.cpp
    PS_func.cpp
)

# relevant only for google test
# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(runTest_all ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTest_Time ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTest_WaterSystem ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTest_Mocks ${GTEST_LIBRARIES} pthread)
