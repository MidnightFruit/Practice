cmake_minimum_required(VERSION 3.10.0)
project(data_struct VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(data_struct INTERFACE)

target_include_directories(data_struct INTERFACE
    ${PROJECT_SOURCE_DIR}/src
)

add_executable(main_app main.cpp)

target_link_libraries(main_app PRIVATE data_struct)

enable_testing()

add_executable(test_hash_table tests/test_hash_table.cpp)
target_link_libraries(test_hash_table PRIVATE data_struct)
add_test(NAME test_hash_table COMMAND test_hash_table)

#add_executable(test_stack tests/test_stack.cpp)
#target_link_libraries(test_stack PRIVATE data_structures)
#add_test(NAME test_stack COMMAND test_stack)

#add_executable(test_tree tests/test_tree.cpp)
#target_link_libraries(test_tree PRIVATE data_structures)
#add_test(NAME test_tree COMMAND test_tree)