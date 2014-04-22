#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "engine.h"

GLFWwindow * w;
config_t cfg;

static void
glfw_error_cb(int error, const char *desc) {
	printf("%s", desc);
}

static void
deinit() {
	if (w) {
		printf("Closing window... ");
		glfwDestroyWindow(w);
		w = NULL;
		printf("OK\n");
	}
		
	printf("Shutting down video... ");
	glfwTerminate();
	printf("OK\n");

	config_destroy(&cfg);
}

static void
init() {
	int width, height;

	config_init(&cfg);
	printf("Loading config... ");
	if (config_read_file(&cfg, "cfg/test.cfg") == CONFIG_FALSE) {
		printf("FAILED!\n");
		exit(EXIT_FAILURE);
	}
	printf("OK\n");

	glfwSetErrorCallback(glfw_error_cb);
	
	printf("Initializing video... ");
	if (!glfwInit()) {
		printf("FAILED!\n");
		exit(EXIT_FAILURE);
	}
	atexit(deinit);
	printf("OK\n");

	printf("Creating window... ");
	config_lookup_int(&cfg, "test.window.size.w", &width);
	config_lookup_int(&cfg, "test.window.size.h", &height);
	if ((w = glfwCreateWindow(width, height, "Derp", NULL, NULL)) == NULL) {
		printf("FAILED!\n");
		exit(EXIT_FAILURE);
	}
	printf("OK\n");

	printf("Setting OpenGL context... ");
	glfwMakeContextCurrent(w);
	printf("OK\n");
}

int
main() {
	init();
	run();
}
