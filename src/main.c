/*
 ============================================================================
 Name        : main.c
 Author      : Students: Fatimah Moallim
 	 	 	 	 	 	 Mona Ibrahim
 	 	 	 	 	 	 Afnan Almogbel
 Description : Qassim University
 	 	 	   Instructor: Dr. Mohamed Othman
 	 	 	   CSC 338 - Compiler Design Project - Phase 7 - Nested if and while statements
 ============================================================================
 */

/* main.c */

#include "global.h"

extern void init();
extern void parse();

int openFiles() /* Open files */
{
	strcpy(ErrorFileName,"errorFile");
	strcat(ErrorFileName,".err");
	errorFile = fopen(ErrorFileName,"w");

	strcpy(InputFileName,"inputFile");
	strcat(InputFileName,".exp");
	inputFile = fopen(InputFileName,"r");
	if( inputFile == NULL )
	   {
	      fprintf(errorFile,"Error in opening inputFile file");
	      return(-1);
	   }

	strcpy(OutputFileName,"outputFile");
	strcat(OutputFileName,".obj");
	outputFile = fopen(OutputFileName,"w");

	return 0;
}

void closeFiles() /* Close files */
{
	fclose(inputFile);
	fclose(outputFile);
	fclose(errorFile);
}

int main(int argc, char** argv) {

	init();
	openFiles();
	parse();
	closeFiles();
    exit(0);

    return (EXIT_SUCCESS);
}
