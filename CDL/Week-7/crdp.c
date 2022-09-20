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

void declarations() {

}

void assign_stat() {

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
					declarations();
					assign_stat();
					t = getToken(fptr);
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