#include <stdlib.h>
#include "test.h"
#include "object.h"

struct triangle_data {
	float angle;
};

static void
triangle_draw(void *data) {
	struct triangle_data *t = data;

	glPushMatrix();
	glRotatef(t->angle, 0.0f, 0.0f, 1.0f);

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

static void
triangle_update(void *data) {
	struct triangle_data *t = data;
	t->angle = glfwGetTime() * 50.0f;
}

struct object *
triangle_create() {
	struct object *obj = malloc(sizeof *obj);
	obj->data = malloc(sizeof(struct triangle_data));
	obj->update = triangle_update;
	obj->render = triangle_draw;
	
	return obj;
}
