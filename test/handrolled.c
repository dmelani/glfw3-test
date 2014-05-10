#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#define MTLLIB "mtllib "
#define OBJ_NAME "o "
#define VERTEX "v "

struct vertex {
	float v[4];
	TAILQ_ENTRY(vertex) list;
};

struct object {
	const char *name;
	const char *material_library;
	TAILQ_HEAD(, vertex) vertices;
};

static void
trim(char *s) {
	s[strcspn(s, "\n\r")] = '\0';
}


struct object *
parse_object(FILE *f) {
	char *tok;
	char linebuf[4096];
	struct object *obj = malloc(sizeof *obj);
	TAILQ_INIT(&obj->vertices);

	while (fgets(linebuf, 4096, f)) {
		trim(linebuf);
		if (strncmp(MTLLIB, linebuf, strlen(MTLLIB)) == 0) {
			obj->material_library = strdup(&linebuf[strlen(MTLLIB)]);
		} else if (strncmp(OBJ_NAME, linebuf, strlen(OBJ_NAME)) == 0) {
			obj->name = strdup(&linebuf[strlen(OBJ_NAME)]);
		} else if (strncmp(VERTEX, linebuf, strlen(VERTEX)) == 0) {
			char *l = &linebuf[strlen(VERTEX)];
			int i = 0;
			struct vertex *v = malloc(sizeof *v);
			memset(v, 0, sizeof *v);

			while ((tok = strsep(&l, " ")) != NULL && i < 4) {
				v->v[i++] = strtof(tok, NULL);
			}

			TAILQ_INSERT_TAIL(&obj->vertices, v, list);
		}
	}
	
	return obj;
}

void
print_object(struct object *o) {
	struct vertex *vn;
	int i = 0;

	printf("Name: %s\n", o->name);
	printf("Vertices: \n");
	TAILQ_FOREACH(vn, &o->vertices, list) {
		printf("\t%d:", i++);
		for (int v_i = 0; v_i < 4; v_i++) {
			printf(" %f", vn->v[v_i]);
		}
		printf("\n");
	}
	printf("Material Library: %s\n", o->material_library);
}

int
main(int argc, const char *argv[]) {
	const char *fname;
	struct object *obj;
	FILE * input;

	if (argc != 2) {
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	fname = argv[1];

	if ((input = fopen(fname, "r")) == NULL) {
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}
	
	obj = parse_object(input);
	print_object(obj);
	return 0;
}
