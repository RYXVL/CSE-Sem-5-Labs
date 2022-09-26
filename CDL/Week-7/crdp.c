#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.c"

///////////////////////////////////
void unGetNextToken(FILE* fptr) {
	fseek(fptr, -strlen(t->tokenName), SEEK_CUR);
}
///////////////////////////////////

void invalid() {
	printf("FALIED");
	exit(0);
}

data_type() {
	if(strcmp("int", t->tokenName)==0 || strcmp("char", t->tokenName)==0) {
		return;
	}
	else invalid();
}

identifier_list_prime() {
	if(strcmp(",", t->tokenName)==0) {
		identifier_list();
	}
}

identifier_list() {
	t = getToken(fptr);
	printToken();
	if(strcmp("id", t->tokenName)==0) {
		t = getToken(fptr);
		printToken();
		if(strcmp(",", t->tokenName)==0) {
			identifier_list_prime();
		}
	}
	else invalid();
}

void declarations() {
	t = getToken(fptr);
	printToken();
	if(strcmp("int", t->tokenName)==0 || strcmp("char", t->tokenName)==0) {
		data_type();
		identifier_list();
		if(strcmp(";", t->tokenName)==0) {
			declarations();
		}
	}
	else { ///////////////////////////////////
		// printf(" %s ", t->tokenName);
		// unGetNextToken(fptr);
		// t = getToken(fptr);
		// printf(" %s ", t->tokenName);
		// printf("check");
	}
}

void assign_stat_prime() {
	t = getToken(fptr);
	printToken();
	if(strcmp("id", t->tokenName)==0 || strcmp("NUM", t->tokenName)==0) {
		t = getToken(fptr);
		printToken();
		if(strcmp(";", t->tokenName)==0) {
			return;
		}
		else invalid();
	}
	else invalid();
}

void assign_stat() {
	// printf("assign check %s", t->tokenName); /////////////////////
	if(strcmp("id", t->tokenName)==0) {
		// printf(" n %c n ", fgetc(fptr));
		t = getToken(fptr);
		printToken();
		// printf("after assign check %s", t->tokenName); /////////////////////
		if(strcmp("=", t->tokenName)==0) {
			assign_stat_prime();
		}
		else invalid();
	}
	else invalid();
}

void printToken() {
	printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col);
}

void program() {
	t = getToken(fptr);
	printToken();
	if(strcmp("main", t->tokenName)==0) {
		t = getToken(fptr);
		printToken();
		if(strcmp("(", t->tokenName)==0) {
			t = getToken(fptr);
			printToken();
			if(strcmp(")", t->tokenName)==0) {
				t = getToken(fptr);
				printToken();
				if(strcmp("{", t->tokenName)==0) {
					declarations();
					// printf(" check after\n"); /////////////////////////
					assign_stat();
					// printf(" check after prime\n"); /////////////////////////
					t = getToken(fptr);
					printToken();
					if(strcmp("}", t->tokenName)==0) {
						return;
					}
					else invalid();
				}
				else invalid();
			}
			else invalid();
		}
		else invalid();
	}
	else invalid();
}

int main() {
	for(int i=0; i<MAX_HASH_SIZE; i++)
		hashSymbol[i] == NULL;
	printf("Enter the first file to be opened: ");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if(!fptr) {
		printf("The file does not exist.\n");
		exit(0);
	}
	program();
	t = getToken(fptr);
	printToken();
	if(strcmp(t->tokenName, "$")==0) printf("SUCCESS");
	else invalid();
	displaySymbolTable();
	fclose(fptr);
	return 0;
}
