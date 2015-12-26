include_directories (${PROJECT_SOURCE_DIR}/include)

add_executable (hw-fw hw-main.cpp HTTPCurlProvider.cpp ISensor.cpp PIRSensor.cpp)
target_link_libraries (hw-fw mraa curl wiringPi ${CMAKE_THREAD_LIBS_INIT})