#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.c"

struct token* t;
FILE* fptr;

void invalid(char tokenName[100], int pos) {
    printf("FAILED - %s %d\n", tokenName, pos);
    exit(0);
}

void printToken(struct token* tk) {
    printf("<%s, %d, %d>\n", tk->tokenName, tk->row, tk->col);
}

char *firstS[3] = {"a", ">", "("};
int findFirstS(char str[100]) {
    for(int i=0; i<3; i++) {
        // printf("@%s-%s@\n", firstS[i], str);
        if(!strcmp(firstS[i], str)) return i;
    }
    return -1;
}
char *followS[3] = {"$", ",", ")"};
int findFollowS(char str[100]) {
    for(int i=0; i<3; i++)
        if(!strcmp(followS[i], str)) return i;
    return -1;
}

char *firstT[3] = {"a", ">", "("};
int findFirstT(char str[100]) {
    for(int i=0; i<3; i++)
        if(!strcmp(firstT[i], str)) return i;
    return -1;
}
char* followT = ")";
int findFollowT(char str[100]) {
    if(!strcmp(followT, str)) return 0;
    return -1;
}

char* firstTPrime = ",";
int findFirstTPrime(char str[100]) {
    if(!strcmp(firstTPrime, str)) return 0;
    return -1;
}
char*followTPrime = ")";
int findFollowTPrime(char str[100]) {
    if(!strcmp(followTPrime, str)) return 0;
    return -1;
}

void S();
void T();
void TPrime();

void S() {
    if(!strcmp(t->tokenName, "a") || !strcmp(t->tokenName, ">")) return;
    else {
        t = getToken(fptr);
        printToken(t);
        if(findFirstT(t->tokenName)>=0)
            T();
        else {
            invalid(t->tokenName, 1);
        }
    }
}

void T() {
    S();
    t = getToken(fptr);
    printToken(t);
    if(findFirstTPrime(t->tokenName)>=0)
        TPrime();
    else if(findFollowTPrime(t->tokenName)>=0)
        return;
    else {
        invalid(t->tokenName, 2);
    }
}

void TPrime() {
    t = getToken(fptr);
    printToken(t);
    if(findFirstS(t->tokenName)>=0) {
        S();
    }
    else {
        invalid(t->tokenName, 3);
    }
    t = getToken(fptr);
    printToken(t);
    if(findFirstTPrime(t->tokenName)>=0)
        TPrime();
    else if(findFollowTPrime(t->tokenName)>=0)
        return;
    else {
        invalid(t->tokenName, 4);
    }
}

int main() {
    t = (struct token*)malloc(sizeof(struct token));
    printf("Enter the first file to be opened: ");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if(!fptr) {
		printf("The file does not exist.\n");
		exit(0);
	}
    
    t = getToken(fptr);
    printToken(t);

    if(findFirstS(t->tokenName)>=0) {
        S();
    }
    else {
        printf("check failed in main find first S\n");
        invalid(t->tokenName, 5);    
    }

    t = getToken(fptr);
    printToken(t);
    // printf("check $");
    if(!strcmp(t->tokenName, "$")) printf("SUCCESS\n");
    else invalid(t->tokenName, 6);

	displaySymbolTable();
	fclose(fptr);
	return 0;
}