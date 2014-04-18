#include "test.h"
#include "engine.h"
#include "scene.h"
extern GLFWwindow * w;

static void
key_cb(GLFWwindow *w, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(w, GL_TRUE);
}

static void
reset_gl() {
	float ratio;
	int width, height;
	
	glfwGetFramebufferSize(w, &width, &height);
	ratio = width / (float) height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void
run() {
	glfwSetKeyCallback(w, key_cb);
	scene_init();

	while (!glfwWindowShouldClose(w)) {
		reset_gl();

		scene_update();
		scene_render();

		glfwSwapBuffers(w);
		glfwPollEvents();
	}
}
