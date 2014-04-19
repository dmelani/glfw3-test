#include <sys/queue.h>
#include <stdlib.h>
#include "test.h"
#include "object.h"
#include "triangle.h"

struct objects {
	struct object *o;
	SLIST_ENTRY(objects) entries;
};

SLIST_HEAD(objectshead, objects) objs = SLIST_HEAD_INITIALIZER(objs);


void
scene_init() {
	SLIST_INIT(&objs);

	struct objects *entry = malloc(sizeof *entry);
	entry->o = triangle_create();
	SLIST_INSERT_HEAD(&objs, entry, entries);
}

void
scene_update() {
	struct objects *entry;
	SLIST_FOREACH(entry, &objs, entries) {
		entry->o->update(entry->o->data);
	}
}

void
scene_render() {
	struct objects *entry;
	SLIST_FOREACH(entry, &objs, entries) {
		entry->o->render(entry->o->data);
	}
}
