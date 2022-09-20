#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.c"

// int main() {
// 	return 0;
// }

void invalid() {
	printf("FALIED");
	exit(0);
}

data_type() {
	// t = getToken(fptr);
	// printf("%s", t->tokenName);
	if(strcmp("int", t->tokenName)==0 || strcmp("char", t->tokenName)==0) {
		return;
	}
	else invalid();
}

identifier_list_prime() {
	// t = getToken(fptr);
	if(strcmp(",", t->tokenName)==0) {
		identifier_list();
	}
	// else printf("%s", t->tokenName);
	// else invalid();
}

identifier_list() {
	t = getToken(fptr);
	// printf("%s", t->tokenName);
	if(strcmp("id", t->tokenName)==0) {
		t = getToken(fptr);
		if(strcmp(",", t->tokenName)==0) {
			identifier_list_prime();
		}
		// identifier_list_prime();
	}
	else invalid();
}

void declarations() {
	// printf("%s", t->tokenName);
	t = getToken(fptr);
	if(strcmp("int", t->tokenName)==0 || strcmp("char", t->tokenName)==0) {
		data_type();
		identifier_list();
		// t = getToken(fptr);
		// printf("%s", t->tokenName);
		// printf("%s", t->tokenName);
		if(strcmp(";", t->tokenName)==0) {
			declarations();
		}
	}
	
	// else invalid();
}

void assign_stat_prime() {
	t = getToken(fptr);
	if(strcmp("id", t->tokenName)==0 || strcmp("NUM", t->tokenName)==0) {
		t = getToken(fptr);
		if(strcmp(";", t->tokenName)==0) {
			return;
		}
		else invalid();
	}
	else invalid();
}

void assign_stat() {
	// t = getToken(fptr);
	if(strcmp("id", t->tokenName)==0) {
		// declarations();
		t = getToken(fptr);
		if(strcmp("=", t->tokenName)==0) {
			assign_stat_prime();
		}
		else invalid();
	}
	else invalid();
}

void program() {
	t = getToken(fptr);
	if(strcmp("main", t->tokenName)==0) {
		t = getToken(fptr);
		if(strcmp("(", t->tokenName)==0) {
			t = getToken(fptr);
			if(strcmp(")", t->tokenName)==0) {
				t = getToken(fptr);
				if(strcmp("{", t->tokenName)==0) {
					// printf("%s", t->tokenName);
					declarations();
					// printf("%s", t->tokenName);
					assign_stat();
					// printf("%s", t->tokenName);
					t = getToken(fptr);
					// printf("%s", t->tokenName);
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
	// printf("%s", t->tokenName);
	if(strcmp(t->tokenName, "$")==0) printf("SUCCESS");
	else invalid();
	// while(1) {
	// 	t = getToken(fptr);
	// 	if(!t) break;
	// 	printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col);
	// }
	displaySymbolTable();
	fclose(fptr);
	return 0;
}
