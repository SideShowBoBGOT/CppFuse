enable_testing()
include(CTest)

add_executable(myTest test.cpp)
target_link_libraries(myTest PRIVATE ${PROJECT_NAME})
target_link_libraries(myTest PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(myTest)