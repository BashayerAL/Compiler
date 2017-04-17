/* init.c */

#include "global.h"

extern int insert(char s[], int tok);

struct entry keywords[] = { /* Keywords array */
	"div", DIV,
	"mod", MOD,
	"if", IF,
	"then", THEN,
	"while", WHILE,
	"do", DO,
	"begin", BEGIN,
	"end", END,
	"sahih", SAHIH,
	"hakiki", HAKIKI,
	"harf", HARF,
	0, 0
};

void init()
{
	struct entry *p;
	for (p = keywords; p->token; p++) /* Insert keywords into the symbol table */
		insert(p->lexptr, p->token);
}
