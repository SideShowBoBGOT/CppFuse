enable_testing()
include(CTest)

add_executable(GeneralTest GeneralTest.cpp)
target_link_libraries(GeneralTest PRIVATE ${PROJECT_NAME})
target_link_libraries(GeneralTest PRIVATE GTest::gtest_main)

add_executable(SpeedUpTest SpeedUpTest.cpp)

include(GoogleTest)
gtest_discover_tests(GeneralTest)