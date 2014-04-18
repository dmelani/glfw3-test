#include "test.h"

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
scene_init() {
}

void
scene_update() {
}

void
scene_render() {
	draw_triangle();
}
