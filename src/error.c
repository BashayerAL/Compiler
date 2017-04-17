/* error.c */

#include "global.h"

void error(char* m)
{
	fprintf(errorFile, "line %d: %s\n", lineno, m); /* Print  the line number and the error message */
	exit(1); /* then halt */
}
