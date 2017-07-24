cmake_minimum_required(VERSION 2.8)
project(nlp_corrector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

set(SOURCE_FILES src/main.cc src/utils.cc src/output.cc src/output_element.cc src/trie_node.cc)
add_executable(nlp_corrector ${SOURCE_FILES})