#include "test.h"
#include "engine.h"
extern GLFWwindow * w;

void
run() {
	while (!glfwWindowShouldClose(w)) {
		glfwPollEvents();
		glfwSwapBuffers(w);
	}
}
