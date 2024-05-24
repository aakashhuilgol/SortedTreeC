# Do not change this file
add_executable(test_tree test_tree.c)
include_directories(${SortedTree_SOURCE_DIR}/tree/inc)
add_test(NAME test_tree COMMAND test_tree)
target_link_libraries(test_tree tree)
