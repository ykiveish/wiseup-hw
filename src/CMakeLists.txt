include_directories (${PROJECT_SOURCE_DIR}/include)

add_executable (hw-fw hw-main.cpp)
target_link_libraries (hw-fw mraa curl)