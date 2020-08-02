add_library(
    gtest_main
    gtest_main.cpp
)

add_executable(
    runTest_all
    water_system_test.cpp
    time_test.cpp
    mocks_test.cpp
)

add_executable(
    runTest_time
    time_test.cpp
)

add_executable(
    runTest_water_system
    water_system_test.cpp
)

add_executable(
    runTest_mocks
    mocks_test.cpp
)

# relevant only for google test
# Link runTests with what we want to test and the GTest and pthread library
message("GTEST_LIBRARIES = ${GTEST_LIBRARIES}")
target_link_libraries(runTest_all ${GTEST_LIBRARIES} pthread test_library gtest_main)
target_link_libraries(runTest_time ${GTEST_LIBRARIES} pthread test_library gtest_main)
target_link_libraries(runTest_water_system ${GTEST_LIBRARIES} pthread test_library gtest_main)
target_link_libraries(runTest_mocks ${GTEST_LIBRARIES} pthread test_library gtest_main)