#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.c"

// first and follow of all productions and functions to search in the respective array

char* firstProgram = "main";
char* followProgram = "$";

char firstDeclaration[2][10] = {"int", "char"};
int findfirstDeclaration(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstDeclaration[i], str)==0) return i;
	return -1;
}
char followDeclaration[2][10] = {"id", "}"};
int findfollowDeclaration(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(followDeclaration[i], str)==0) return i;
	return -1;
}

char firstDataType[2][10] = {"int", "char"};
int findfirstDataType(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstDataType[i], str)==0) return i;
	return -1;
}
char* followDataType = "id";

char* firstIDList = "id";
char* followIDList = ";";

char firstIDListPrime[2][10] = {",", "["};
int findfirstIDListPrime(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstIDListPrime[i], str)==0) return i;
	return -1;
}
char* followIDListPrime = ";";

char* firstIDListPrimePrime = ",";
char* followIDListPrimePrime = ";";

char* firstStatementList = "id";
char* followStatementList = "}";

char* firstStatement = "id";
char followStatement[2][10] = {"id", "}"};
int findfollowStatement(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(followStatement[i], str)==0) return i;
	return -1;
}

char* firstAssignStat = "id";
char* followAssignStat = ";";
// int findfollowAssignStat(char *str) {
// 	for(int i=0; i<2; i++)
// 		if(strcmp(followAssignStat[i], str)==0) return i;
// 	return -1;
// }

char firstExpn[2][10] = {"id", "NUM"};
int findfirstExpn(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstExpn[i], str)==0) return i;
	return -1;
}
char* followExpn = ";";
// int findfollowExpn(char *str) {
// 	for(int i=0; i<2; i++)
// 		if(strcmp(followExpn[i], str)==0) return i;
// 	return -1;
// }

char firstSimpleExpn[2][10] = {"id", "NUM"};
int findfirstSimpleExpn(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstSimpleExpn[i], str)==0) return i;
	return -1;
}
char followSimpleExpn[7][10] = {"==", "!=", "<=", ">=", "<", ">", ";"};
int findfollowSimpleExpn(char *str) {
	for(int i=0; i<7; i++)
		if(strcmp(followSimpleExpn[i], str)==0) return i;
	return -1;
}

char firstTerm[2][10] = {"id", "NUM"};
int findfirstTerm(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstTerm[i], str)==0) return i;
	return -1;
}
char followTerm[9][10] = {"+", "-", "==", "!=", "<=", ">=", "<", ">", ";"};
int findfollowTerm(char *str) {
	for(int i=0; i<9; i++)
		if(strcmp(followTerm[i], str)==0) return i;
	return -1;
}

char firstFactor[2][10] = {"id", "NUM"};
int findfirstFactor(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstFactor[i], str)==0) return i;
	return -1;
}
char followFactor[12][10] = {"*", "/", "%", "+", "-", "==", "!=", "<=", ">=", "<", ">", ";"};
int findfollowFactor(char *str) {
	for(int i=0; i<12; i++)
		if(strcmp(followFactor[i], str)==0) return i;
	return -1;
}

char firstRelop[6][10] = {"==", "!=", "<=", ">=", "<", ">"};
int findfirstRelop(char *str) {
	for(int i=0; i<6; i++)
		if(strcmp(firstRelop[i], str)==0) return i;
	return -1;
}
char followRelop[2][10] = {"id", "NUM"};
int findfollowRelop(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(followRelop[i], str)==0) return i;
	return -1;
}

char firstTprime[3][10] = {"*", "/", "%"};
int findfirstTprime(char *str) {
	for(int i=0; i<3; i++)
		if(strcmp(firstTprime[i], str)==0) return i;
	return -1;
}
char followTprime[9][10] = {"+", "-", "==", "!=", "<=", ">=", "<", ">", ";"};
int findfollowTprime(char *str) {
	for(int i=0; i<9; i++)
		if(strcmp(followTprime[i], str)==0) return i;
	return -1;
}

char firstSeprime[2][10] = {"+", "-"};
int findfirstSeprime(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstSeprime[i], str)==0) return i;
	return -1;
}
char followSeprime[7][10] = {"==", "!=", "<=", ">=", "<", ">", ";"};
int findfollowSeprime(char *str) {
	for(int i=0; i<7; i++)
		if(strcmp(followSeprime[i], str)==0) return i;
	return -1;
}

char firstAddop[2][10] = {"+", "-"};
int findfirstAddop(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstAddop[i], str)==0) return i;
	return -1;
}
char followAddop[2][10] = {"id", "NUM"};
int findfollowAddop(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(followAddop[i], str)==0) return i;
	return -1;
}

char firstEprime[6][10] = {"==", "!=", "<=", ">=", "<", ">"};
int findfirstEprime(char *str) {
	for(int i=0; i<6; i++)
		if(strcmp(firstEprime[i], str)==0) return i;
	return -1;
}
char* followEprime = ";";
// int findfollowEprime(char *str) {
// 	for(int i=0; i<2; i++)
// 		if(strcmp(followEprime[i], str)==0) return i;
// 	return -1;
// }

char firstMulop[3][10] = {"*", "/", "%"};
int findfirstMulop(char *str) {
	for(int i=0; i<3; i++)
		if(strcmp(firstMulop[i], str)==0) return i;
	return -1;
}
char followMulop[2][10] = {"id", "NUM"};
int findfollowMulop(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(followMulop[i], str)==0) return i;
	return -1;
}

// recursive functions for all the different productions

void declarations() {
	t = getToken(fptr);
	printToken();
	if(strcmp(firstIDList, t->tokenName)==0)
		identifier_list();
	else return;
	// printf("check - %s\n", t->tokenName); //////////////////////////////
	if(strcmp(";", t->tokenName)==0) {
		t = getToken(fptr);
		printToken();
		if(findfirstDeclaration(t->tokenName)!=-1) {
			declarations();
			if(strcmp(firstStatementList, t->tokenName)==0) statementList();
			else if(strcmp(followStatementList, t->tokenName)==0) return;
			else {
				printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "}");
				exit(0);
			}
		}
		else if(findfollowDeclaration(t->tokenName)!=-1) {
			if(strcmp(firstStatementList, t->tokenName)==0) statementList();
			else if(strcmp(followStatementList, t->tokenName)==0) return;
			else {
				printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "}");
				exit(0);
			}
		}
		else {
			printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\" or \"%s\".\n", t->row, t->col, "int", "char", "id", "}");
			exit(0);
		}
	}
	else {
		printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ";");
		exit(0);
	}
}

identifier_list() {
		if(strcmp("id", t->tokenName)!=-1) {
		t = getToken(fptr);
		printToken();
		if(findfirstIDListPrime(t->tokenName)!=-1)
			identifier_list_prime();
		else if(strcmp(followIDListPrime, t->tokenName)==0) return;
		else {
			printf("Error at row: %d, col: %d, expected \"%s\", \"%s\" or \"%s\".\n", t->row, t->col, ",", "[", ";");
			exit(0);
		}
	}
	else {
		printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "id");
		exit(0);
	}
}

identifier_list_prime() {
	if(strcmp(t->tokenName, ",")==0)
		identifier_list();
	else  {
		t = getToken(fptr);
		printToken();
		if(strcmp(t->tokenName, "NUM")==0) {
			t = getToken(fptr);
			printToken();
			if(strcmp(t->tokenName, "]")==0) {
				t = getToken(fptr);
				printToken();
				if(strcmp(firstIDListPrimePrime, t->tokenName)==0)
					identifier_list_prime_prime();
				else if(strcmp(followIDListPrimePrime, t->tokenName)==0)
					return;
				else {
					printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, ",", ";");
					exit(0);
				}
			}
			else {
				printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "]");
				exit(0);
			}
		}
		else {
			printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "NUM");
			exit(0);
		}
	}
}

identifier_list_prime_prime() {
	identifier_list();
}

void statementList() {
	// printf("statementList check - %s\n", t->tokenName); //////////////////////////////
	statement();
	// printf("check - %s\n", t->tokenName);
	t = getToken(fptr);
	printToken();
	// printf("check - %s\n", t->tokenName);
	if(strcmp(firstStatementList, t->tokenName)==0) {
		// printf("check firstStatementList - %s\n", t->tokenName);
		statementList();
	}
	else if(strcmp(followStatementList, t->tokenName)==0) return;
	else {
		printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "}");
		exit(0);
	}
}

void statement() {
	// printf("statement check - %s\n", t->tokenName); //////////////////////////////
	assignStat();
}

void assignStat() {
	// printf("assignStat check - %s\n", t->tokenName); //////////////////////////////
	t = getToken(fptr);
	printToken();
	if(strcmp(t->tokenName, "=")==0) {
		// printf("inside expn check - %s\n", t->tokenName); //////////////////////////////
		expn();
	}
	else {
		printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "=");
		exit(0);
	}
}

void expn() {
	t = getToken(fptr);
	printToken();
	// printf("check expn - %s\n", t->tokenName);
	// printf("ehbvhvgfwejbfbgff");
	if(findfirstExpn(t->tokenName)!=-1) {
		// printf("inside first of expn check - %s\n", t->tokenName); //////////////////////////////
		simpleExpn();
		if(findfirstEprime(t->tokenName)!=-1)
			ePrime();
		else if(strcmp(followEprime, t->tokenName)==0) return;
		else {
			printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", or \"%s\".\n", t->row, t->col, "id", "}", "==", "!=", "<=", ">=", "<", ">");
			exit(0);
		}
	}
	else {
		printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "NUM");
		exit(0);
	}
}

void simpleExpn() {
		term();
		// printf("check beta - %s\n", t->tokenName);
		// printf("after term check - %s\n", t->tokenName); //////////////////////////////
		// extra ; encountered
		if(findfirstSeprime(t->tokenName)!=-1) sePrime();
		else if(findfollowSeprime(t->tokenName)!=-1) return;
		else {
			printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", or \"%s\".\n", t->row, t->col, "id", "}", "+", "-", "==", "!=", "<=", ">=", "<", ">");
			exit(0);
		}
}

void ePrime() {
	// printf("check - %s\n", t->tokenName); //////////////////////////////
		t = getToken(fptr);
		printToken();
		// printf("check - %s\n", t->tokenName); //////////////////////////////
		if(findfirstSimpleExpn(t->tokenName)!=-1)
			simpleExpn();
		else {
			printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "NUM");
			exit(0);
		}
}

void term() {
	// printf("check - %s\n", t->tokenName); //////////////////////////////
	// printf("check factor - %s\n", t->tokenName);
	factor();
	t = getToken(fptr);
	printToken();
	// printf("check after factor - %s\n", t->tokenName);
	// printf("after factor check - %s - %d\n", t->tokenName, findfirstTprime(t->tokenName)); //////////////////////////////
	// printf("check - %s %d\n", t->tokenName, findfirstTprime(t->tokenName)); //////////////////////////////
	if(findfirstTprime(t->tokenName)!=-1) {
		// printf("tprime check 123 - %s\n", t->tokenName); //////////////////////////////
		tPrime();
		// printf("after tprime check - %s\n", t->tokenName); //////////////////////////////
	}
	else if(findfollowTprime(t->tokenName)!=-1) return;
	else {
		printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\" or \"%s\".\n", t->row, t->col, "*", "/", "%", "id", "}", "+", "-", "==", "!=", "<=", ">=", "<", ">");
		exit(0);
	}
}

void sePrime() {
	// t = getToken(fptr);
	// printToken();
	printf("check seprime - %s\n", t->tokenName);
	if(findfirstAddop(t->tokenName)==-1) {
		printf("error found %s", t->tokenName);
		printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "+", "-");
		exit(0);
	}
	else if(findfollowSeprime(t->tokenName)!=-1) return;
	t = getToken(fptr);
	printToken();
	printf("primealphabeta - %s\n", t->tokenName);
	term();
	// sePrime();
	if(findfirstSeprime(t->tokenName)!=-1) sePrime();
	else if(findfollowSeprime(t->tokenName)!=-1) return;
	else {
		printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", or \"%s\".\n", t->row, t->col, "id", "}", "+", "-", "==", "!=", "<=", ">=", "<", ">");
		exit(0);
	}
}

void factor() {
	if(findfirstFactor(t->tokenName)==-1) {
		printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "NUM");
		exit(0);
	}
	// printf("alpha check - %s\n", t->tokenName); //////////////////////////////
}

void tPrime() {
	t = getToken(fptr);
	printToken();
	// printf("tprime fn check - %s\n", t->tokenName); //////////////////////////////
	factor();
	t = getToken(fptr);
	printToken();
	// if(strcmp(";", t->tokenName)==0) return; /////////////////////////
	// printf("hjibfisdhbf dfkih fswdf check - %s\n", t->tokenName); //////////////////////////////
	if(findfirstTprime(t->tokenName)!=-1) tPrime();
	else if (findfollowTprime(t->tokenName)!=-1) return;
	else {
		// printf("checkalphaomega");
		printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\" or \"%s\".\n", t->row, t->col, "*", "/", "%", "id", "}", "+", "-", "==", "!=", "<=", ">=", "<", ">");
		exit(0);
	}
}

void printToken() {
	printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col);
}

void program() {
	t = getToken(fptr);
	printToken();
	if(strcmp(firstProgram, t->tokenName)==0) {
		t = getToken(fptr);
		printToken();
		if(strcmp("(", t->tokenName)==0) {
			t = getToken(fptr);
			printToken();
			if(strcmp(")", t->tokenName)==0) {
				t = getToken(fptr);
				printToken();
				if(strcmp("{", t->tokenName)==0) {
					t = getToken(fptr);
					printToken();
					if(findfirstDeclaration(t->tokenName)!=-1) {
						// printf("before declarations check - %s\n", t->tokenName); //////////////////////////////
						declarations();
						// printf("after declarations inside first declarations check - %s\n", t->tokenName); //////////////////////////////
						if(strcmp(firstStatementList, t->tokenName)==0) statementList();
						else if(strcmp(followStatementList, t->tokenName)==0) return;
						else {
							printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "}");
							exit(0);
						}
					}
					else if(findfollowDeclaration(t->tokenName)!=-1) {
						// printf("after declarations follow declarations check - %s\n", t->tokenName); //////////////////////////////
						if(strcmp(firstStatementList, t->tokenName)==0) statementList();
						else if(strcmp(followStatementList, t->tokenName)==0) return;
						else {
							printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "}");
							exit(0);
						}
					}
					else {
						printf("Error at row: %d, col: %d, expected \"%s\", \"%s\", \"%s\" or \"%s\".\n", t->row, t->col, "int", "char", "id", "}");
						exit(0);
					}
				}
				else {
					printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "{");
					exit(0);
				}
			}
			else {
				printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ")");
				exit(0);
			}
		}
		else {
			printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "(");
			exit(0);
		}
	}
	else {
		printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, firstProgram);
		exit(0);
	}
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
	else printf("ERROR AFTER COMPILING\n");
	displaySymbolTable();
	fclose(fptr);
	return 0;
}
