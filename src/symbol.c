/* symbol.c */

#include "global.h"

extern void error(char* m);

char lexemes[STRMAX];
int lastchar = -1;
struct entry symtable[SYMMAX]; /* Symbols Table */
int lastentry = 0;

int lookup(char s[]) /* Search for s[] in the symbol table*/
{
	int p;
	for (p = lastentry; p > 0; p = p-1) /* Check if s[] is in the symbol table */
	    if (strcmp(symtable[p].lexptr, s) == 0)
	        return p; /* then return its index */

	return 0; /* otherwise return 0 */
}

int insert(char s[], int tok) /* Insert s[] and its token into the symbol table*/
{
	int len;
	len = strlen(s);

	if (lastentry + 1 >= SYMMAX)
		error("symbol table full"); /* Raise an error if the symbol table is full*/

	if (lastchar + len + 1 >= STRMAX)
		error("lexemes array full"); /* Raise an error if the lexemes array is full*/

	lastentry = lastentry + 1; /* Update the last entry counter*/

	symtable[lastentry].token = tok;

	symtable[lastentry].lexptr = &lexemes[lastchar + 1];

	lastchar = lastchar + len + 1;

	strcpy(symtable[lastentry].lexptr, s);

	return lastentry;
}
