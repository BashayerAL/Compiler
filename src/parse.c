/* parse.c */

#include "global.h"

extern struct entry symtable[SYMMAX];
extern int lexan();
extern void emit(int t, int tval);
extern void error(char* m);
extern int lookup(char s[]);

void parse();
void expr();
void term();
void factor();
void stmt();
void cs();
void decs();
void dec();
void match(int t);
void push(int item);
void pop();

void push(int item);
void pop();

int stack[STACKSIZE];
int top = -1;

int ifs = 0;
int whiles = 0;


void parse() /* Parse start */
{
		lookahead = lexan(); /* Call the lexical analyzer to read the first character */
		fprintf(outputFile, "dataStart\n");
		declare = 1; /* Start of declarations */
		decs();
		fprintf(outputFile, "dataEnd\ncodeStart\n");
		match(BEGIN);
		stmt();
		match(END);
		fprintf(outputFile, "codeEnd\n");
		match(DONE);

}

void expr() /* Parse expr */
{
	int t;
	term();

	while(1) {
	   switch (lookahead) {
	     case '+': case '-':
	        t = lookahead;
	        match(lookahead); term(); emit(t, NONE);
	        continue;
	     default:
                return;
           }
	}
}

void term() /* Parse term */
{
	int t;
	factor();
	while(1){
	     switch (lookahead) {
	        case '*': case '/': case DIV: case MOD:
                    t = lookahead;
                    match(lookahead); factor(); emit(t, NONE);
                    continue;
	        default:
	        	return;
             }
	}
}

void factor() /* Parse factor */
{
	switch (lookahead) {
	case '(':
		match ('('); expr(); match(')'); break;
	case NUM:
		emit(NUM, tokenval);
		match(NUM); break;
	case ID:
		emit(ID, tokenval);
		match(ID);
		break;
	default:
		error("syntax error");
	}
}

void stmt() /* Parse stmt */
{
	int tval;
	switch (lookahead) {
	case ID:
		tval=tokenval;
		match(ID);
		match('=');
		expr();
		fprintf(outputFile, "Pop %s\n", symtable[tval].lexptr);
		break;
	case IF:
		ifs++;
		push(ifs);
		match(IF);
		match('(');
		expr();
		match(')');
		fprintf(outputFile, "Pop r2\nCmp%d r2,0\nBe else%d\n",stack[top],stack[top]);
		match(THEN);
		stmt();
		fprintf(outputFile, "Else%d:\n",stack[top]);
		pop();
		break;
	case WHILE:
		whiles++;
		push(whiles);
		match(WHILE);
		fprintf(outputFile, "While%d\n",stack[top]);
		match('(');
		expr();
		match(')');
		fprintf(outputFile, "Pop r2\nCmp%d r2,0\nBe end while%d\n",stack[top],stack[top]);
		match(DO);
		stmt();
		fprintf(outputFile, "B while%d\nEnd while%d:\n",stack[top],stack[top]);
		pop();
		break;
	case BEGIN:
		match(BEGIN); cs(); match(END);
		break;
	default:
		error("syntax error");
	}
}

void cs() /* Parse cs */
{
	while(lookahead!=END){
		stmt();
		match (';');
		cs();
	}
}

void decs() /* Parse decs */
{
	while(lookahead!=BEGIN){
		dec();
		match(';');
		decs();
	}
	declare = 0; /* End of declarations */
}

void dec() /* Parse dec */
{
	int tval;
	switch(lookahead){
		case SAHIH:
			match(SAHIH);
			tval=tokenval;
			match(ID);
			fprintf(outputFile, "%s DW ?\n", symtable[tval].lexptr);
			break;
		case HAKIKI:
			match(HAKIKI);
			tval=tokenval;
			match(ID);
			fprintf(outputFile, "%s DD ?\n", symtable[tval].lexptr);
			break;
		case HARF:
			match(HARF);
			tval=tokenval;
			match(ID);
			fprintf(outputFile, "%s DB ?\n", symtable[tval].lexptr);
			break;
		default:
			error("syntax error");

	}
}

void match(t)
	int t;
{
	if (lookahead == t) { /* Check if lookahead is the expected character or not */
		lookahead = lexan();
	}
	else error ("syntax error");
}

/* Stack Methods*/

void push(int item)
{
	if(top==STACKSIZE-1)
	{
		error("Stack is Full");
	}
	else
	{
		top++;
		stack[top] = item;
	}
}

void pop()
{
	if(top==-1)
	{
		error("Stack is Empty");
	}
	else
	{
		top--;
	}
}
