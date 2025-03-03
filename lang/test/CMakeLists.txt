add_executable(test_map map_test.cc)
target_link_libraries(test_map lang gtest gtest_main)
target_include_directories(test_map PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME lang/map COMMAND test_map WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lang/)