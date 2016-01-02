#include "RaspiStill.h"

int main (int argc, const char **argv) {
	const char *my_argv[15] = { "args", "-w", "640", "-h", "480", "-q", "5", "-o", "pic.jpg", "-tl", "100", "-t", "9999999", "-th", "0:0:0" };
	int my_argc = 15;
   
	mmal_camera (my_argc, my_argv);
	
	return 0;
}