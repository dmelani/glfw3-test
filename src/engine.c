#include "test.h"
#include "engine.h"
extern GLFWwindow * w;

static void
key_cb(GLFWwindow *w, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GL_TRUE);
}

void
run() {
	glfwSetKeyCallback(w, key_cb);

	while (!glfwWindowShouldClose(w)) {
		glfwPollEvents();
		glfwSwapBuffers(w);
	}
}
