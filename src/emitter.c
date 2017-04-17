/* emitter.c */

#include "global.h"

extern struct entry symtable[SYMMAX];

void emit(t, tval) /* Print tokens or their values */
	int t, tval;
{
	switch(t) {
		case '+':
			fprintf(outputFile, "Pop r1\nPop r2\nAdd r2, r1\nPush r2\n");
			break;
		case '-':
			fprintf(outputFile, "Pop r1\nPop r2\nSub r2, r1\nPush r2\n");
			break;
		case '*':
			fprintf(outputFile, "Pop r1\nPop r2\nMult r2, r1\nPush r2\n");
			break;
		case '/':
			fprintf(outputFile, "Pop r1\nPop r2\nRdiv r2, r1\nPush r2\n");
			break;
		case DIV:
			fprintf(outputFile, "Pop r1\nPop r2\nDiv r2, r1\nPush r2\n");
			break;
		case MOD:
			fprintf(outputFile, "Pop r1\nPop r2\nMOD r2, r1\nPush r2\n");
			break;
		case NUM:
			fprintf(outputFile, "Push %d\n", tval);
			break;
		case ID:
			fprintf(outputFile, "Push %s  \n", symtable[tval].lexptr);
			break;
		default:
			fprintf(outputFile, "token %d, tokenval %d\n", t, tval);
		}
}
