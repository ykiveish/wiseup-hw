#ifndef RASPISTILL_H_
#define RASPISTILL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*frame_recieved_callback) (long long, void *);

typedef struct {
    unsigned int            running;
    frame_recieved_callback callback;
    void *                  args;
} mmal_camera_context_t;

int mmal_camera (int argc, const char **argv, mmal_camera_context_t* ctx);
#ifdef __cplusplus
   }  /* extern "C" */
#endif

#endif