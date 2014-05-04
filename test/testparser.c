#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct vertex {
	float x;
	float y;
	float z;
	float w;
	TAILQ_ENTRY(vertex) list;
};

struct object {
	const char *name;
	TAILQ_HEAD(, vertex) vertices;
};

static struct object obj;

FILE *input;

void yyerror(char *message);

#define YY_INPUT(buf, result, max) {				\
	int c = getc(input);					\
	result = (EOF == c) ? 0 : (*(buf) = c, 1);		\
}

static void
add_vertices(float x, float y, float z, float w) {
	struct vertex *v = malloc(sizeof *v);
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = w;
	TAILQ_INSERT_TAIL(&obj.vertices, v, list);
}

#include "objparser.peg.c"

int
main(int argc, const char *argv[]) {
	const char *fname;

	if (argc != 2) {
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	fname = argv[1];
	if ((input = fopen(fname, "r")) == NULL) {
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}

	TAILQ_INIT(&obj.vertices);
	if (!yyparse()) {
		printf("Failed to parse object file: %s", fname);
		exit(EXIT_FAILURE);
	}
	printf("Obj name: %s\n", obj.name);

	return 0;
}
