enable_testing()

add_executable(GeneralTest test.cpp)
target_link_libraries(GeneralTest PRIVATE ${PROJECT_NAME})
target_link_libraries(GeneralTest PRIVATE gtest_main)

add_test(GeneralGTest GeneralTest)