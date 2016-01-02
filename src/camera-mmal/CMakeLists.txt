include_directories(/opt/vc/include)
include_directories(/opt/vc/include/EGL)
include_directories(/opt/vc/include/interface)
include_directories(/opt/vc/include/interface/vcos)
include_directories(/opt/vc/include/interface/vcos/pthreads)
include_directories(/opt/vc/include/interface/vmcs_host/linux)
include_directories(${PROJECT_SOURCE_DIR}/src/camera-mmal)

link_directories (
   /opt/vc/lib/
   ${PROJECT_SOURCE_DIR}/src/camera-mmal
)

set (GL_SCENE_SOURCES
   gl_scenes/models.c
   gl_scenes/mirror.c
   gl_scenes/yuv.c
   gl_scenes/sobel.c
   gl_scenes/square.c
   gl_scenes/teapot.c)

set (COMMON_SOURCES
   RaspiCamControl.c
   RaspiCLI.c
   RaspiPreview.c)

add_library (raspistill SHARED ${COMMON_SOURCES} RaspiStill.c  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})

set (MMAL_LIBS mmal_core mmal_util mmal_vc_client)

target_link_libraries (raspistill ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m ${CMAKE_THREAD_LIBS_INIT})
