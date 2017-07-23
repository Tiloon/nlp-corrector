cmake_minimum_required(VERSION 3.5)
project(nlp_corrector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp src/trieNode.cpp)
add_executable(nlp_corrector ${SOURCE_FILES})