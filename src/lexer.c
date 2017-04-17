/* lexer.c */

#include "global.h"

extern struct entry symtable[SYMMAX];
extern void error(char* m);
extern int lookup(char s[]);
extern int insert(char s[], int tok);

char lexbuf[BSIZE]; /* Lexeme Buffer*/
int lineno = 1;
int tokenval = NONE;

int lexan()
{
	int t;

	while(1) {
		t = getc(inputFile); /* Read the content of the input file */
		if (t == ' ' || t == '\t'); /* Ignore white spaces */
		else if (t == '#') /* Ignore one-line comments */
		{
			while(t!='\n'){
				t = getc(inputFile);
			}
			lineno = lineno + 1;
		}
		else if (t == '@') /* Ignore multi-line comments */
		{
			t = getc(inputFile);
			while(t!='@'){
				if (t == '\n')
					lineno = lineno + 1;
				t = getc(inputFile);
			}
		}
		else if (t == '\n'){ /* New line */
			lineno = lineno + 1;
		}
		else if (isdigit (t)) { /* Read integers */
			ungetc(t, inputFile); /* Push t back */
			fscanf(inputFile, "%d", &tokenval);
			return NUM;
		}
		else if (isalpha(t)) { /* Read identifiers */
			int p, b = 0;
		    while (isalnum(t)) {
		    	lexbuf[b] = t;
		        t = getc(inputFile);
		        b = b + 1;
		        if (b >= BSIZE)
		        	error("compiler error");
		        }
		    	lexbuf[b] = EOS;
		        if (t != EOF)
		        	ungetc(t, inputFile);
		        p = lookup(lexbuf); /* Search for the identifier in the symbol table */
		        if(p!=0 && declare==1 && symtable[p].token==ID) /* Check if the identifier is in the symbol table and declare is 1 */
		        	error("re-declared variable"); /* then raise an re-declared variable error */
		        else if(p==0 && declare==0) /* Else check if the identifier is not in the symbol table and declare is 0 */
		        	error("undeclared variable"); /* then raise an undeclared variable error */
		        else if(p == 0 && declare==1) /* Else check if the identifier is not in the symbol table and declare is 1 */
		        	p = insert(lexbuf, ID); /* then insert it */
		        tokenval = p;
		        return symtable[p].token;
		}
		else if (t == EOF){ /* End of file */
			return DONE;
		}
		else { /* Others */
			tokenval = NONE;
		    return t;
		}
	}
}
