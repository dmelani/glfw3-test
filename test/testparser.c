#include <stdio.h>
#include "objparser.peg.c"

int
main() {
	while(yyparse());
	return 0;
}
