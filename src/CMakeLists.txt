include_directories (${PROJECT_SOURCE_DIR}/include)
include_directories (${PROJECT_SOURCE_DIR}/src/camera-mmal)
include_directories (${PROJECT_SOURCE_DIR}/src/streamer/include)

add_subdirectory (camera-mmal)
add_subdirectory (streamer)

add_executable (hw-fw 	hw-main.cpp
						uipc.cpp
                        Streamer.cpp
						RESTApi.cpp 
						HTTPCurlProvider.cpp 
						ISensor.cpp 
                        IConnector.cpp
                        IService.cpp
						GenericSensor.cpp 
						PIRSensor.cpp 
						DHTSensor.cpp
                        MMALCameraService.cpp 
						UDSConnector.cpp
                        FaceRecognitionService.cpp)
target_link_libraries (hw-fw mraa curl wiringPi raspistill streamer ${CMAKE_THREAD_LIBS_INIT})