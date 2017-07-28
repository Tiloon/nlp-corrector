cmake_minimum_required(VERSION 2.8)
project(nlp_corrector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -g")

set(SOURCE_FILES_COMP src/compiler/main_compiler.cc src/compiler/trie_node.cc)
add_executable(TextMiningCompiler ${SOURCE_FILES_COMP})

set(SOURCE_FILES_SEARCH src/search/main_search.cc src/search/lev.cc src/search/output.cc src/search/bin_node.cc
        src/search/bare_trie_helper.cc)
add_executable(TextMiningApp ${SOURCE_FILES_SEARCH})

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API
documentation (requires Doxygen)" ${DOXYGEN_FOUND})


add_custom_target(doc
            COMMAND doxygen doc/doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
