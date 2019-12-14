/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
#pragma warning(disable:4996)
#include "util.h"
#include "scan.h"
#include "PARSE.H"
#include "globals.h"
#include "tiny.h"

int lineno = 0;
FILE* source;
FILE* listing;
FILE* code;

int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

void tiny(string sourcePath, string treePath)
{
	TreeNode* syntaxTree;
	char pgm[120]; /* source code file name */
	strcpy(pgm, sourcePath.c_str());
	if (strchr(pgm, '.') == NULL)
		strcat(pgm, ".tny");
	source = fopen(pgm, "r");
	if (source == NULL)
	{
		fprintf(stderr, "File %s not found\n", pgm);
		exit(1);
	}
	listing = fopen(treePath.c_str(), "w");
	fprintf(listing, "\nTINY COMPILATION: %s\n", pgm);
	syntaxTree = parse();
	fprintf(listing, "\nSyntax tree:\n");
	printTree(syntaxTree);
	fclose(source);
	fclose(listing);
}

