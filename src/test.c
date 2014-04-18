#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

GLFWwindow * w;

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
}

static void
init() {
	glfwSetErrorCallback(glfw_error_cb);
	
	printf("Initializing video... ");
	if (!glfwInit())
		exit(EXIT_FAILURE);
	atexit(deinit);
	printf("OK\n");

	printf("Creating window... ");
	if ((w = glfwCreateWindow(800, 600, "Derp", glfwGetPrimaryMonitor(), NULL)) == NULL)
		exit(EXIT_FAILURE);
	printf("OK\n");
	
}

int
main() {
	init();
}
