#include <stdio.h>
#include <stdlib.h>

FILE *input;

void yyerror(char *message);

#define YY_INPUT(buf, result, max) {				\
	int c = getc(input);					\
	result = (EOF == c) ? 0 : (*(buf) = c, 1);		\
}

#include "objparser.peg.c"

int
main(int argc, const char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((input = fopen(argv[1], "r")) == NULL) {
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}
	while(yyparse());
	return 0;
}
