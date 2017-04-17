/* global.h */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE  128
#define NONE   -1
#define EOS    '\0' /* eos Token */

#define NUM    256 /* Numbers Token */
#define DIV    257 /* div Token */
#define MOD    258 /* mod Token */
#define ID     259 /* Identifiers Token */
#define DONE   260 /* eof Token */

#define IF     261 /* if Token */
#define THEN   262 /* then Token */
#define WHILE  263 /* while Token */
#define DO     264 /* do Token */
#define BEGIN  265 /* begin Token */
#define END    266 /* end Token */

#define SAHIH  267 /* sahih Token */
#define HAKIKI 268 /* hakiki Token */
#define HARF   269 /* harf Token */

int declare; /* 0 or 1 is assigned to declare */

int tokenval;

int lineno; /* Lines number counter*/

struct entry {
   char *lexptr;
   int token;
   };

int lookahead;

#define STRMAX 999
#define SYMMAX 100

char InputFileName[80], OutputFileName[80], ErrorFileName [80];

FILE *inputFile; /* Input File */
FILE *outputFile; /* Output File */
FILE *errorFile; /* Error File */

#define STACKSIZE 100 /* Stack Size */

#endif
