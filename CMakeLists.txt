cmake_minimum_required (VERSION 2.8)
project (sensors-fw)

SET(COMPILE_DEFINITIONS -Werror)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
FIND_PACKAGE (Threads)

link_directories (
   /opt/vc/lib/
)

include_directories (
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory (src)
