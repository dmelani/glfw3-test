#include "test.h"
#include "engine.h"
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

static void
draw_triangle() {
	glPushMatrix();
	glRotatef((float) glfwGetTime() * 50.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glPopMatrix();
}

void
run() {
	glfwSetKeyCallback(w, key_cb);

	while (!glfwWindowShouldClose(w)) {
		reset_gl();
		draw_triangle();
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
}
