#ifndef OBJECT_H
#define OBJECT_H
struct object {
	void *data;
	void (*update)(void *data);
	void (*render)(void *data);
};
#endif
