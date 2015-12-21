cmake_minimum_required (VERSION 2.8)
project (sensors-fw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories (
        ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory (src)
