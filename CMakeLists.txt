cmake_minimum_required(VERSION 2.8)
project(nlp_corrector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O3")

set(SOURCE_FILES_COMP src/main_compiler.cc src/utils.cc src/output.cc src/trie_node.cc)
add_executable(TextMiningCompiler ${SOURCE_FILES_COMP})

set(SOURCE_FILES_SEARCH src/main_search.cc src/utils.cc src/output.cc src/trie_node.cc)
add_executable(TextMiningApp ${SOURCE_FILES_SEARCH})