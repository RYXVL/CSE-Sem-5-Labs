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

char *firstS[3] = {"(", "a", "d"};
char *followS[3] = {"b", ")", "$"};
int findFirstS(char str[100]) {
    for(int i=0; i<3; i++)
        if(strcmp(firstS[i], str)==0) return i;
    return -1;
}
int findFollowS(char str[100]) {
    for(int i=0; i<3; i++)
        if(strcmp(followS[i], str)==0) return i;
    return -1;
}

char *firstU[3] = {"(", "a", "d"};
char *followU[5] = {"a", "c", "b", ")", "$"};
int findFirstU(char str[100]) {
    for(int i=0; i<3; i++)
        if(strcmp(firstU[i], str)==0) return i;
    return -1;
}
int findFollowU(char str[100]) {
    for(int i=0; i<5; i++)
        if(strcmp(followU[i], str)==0) return i;
    return -1;
}

char *firstV = "a";
char *followV[4] = {"c", "b", ")", "$"};
int findFirstV(char str[100]) {
    if(strcmp(firstV, str)==0) return 0;
    return -1;
}
int findFollowV(char str[100]) {
    for(int i=0; i<4; i++)
        if(strcmp(followV[i], str)==0) return i;
    return -1;
}

char *firstW = "c";
char *followW[3] = {"b", ")", "$"};
int findFirstW(char str[100]) {
    if(strcmp(firstW, str)==0) return 0;
    return -1;
}
int findFollowW(char str[100]) {
    for(int i=0; i<3; i++)
        if(strcmp(followW[i], str)==0) return i;
    return -1;
}

void S();
void U();
void V();
void W();

void S() {
    U();
    t = getToken(fptr);
    printToken(t);
    printf("check 101\n");
    if(findFirstV(t->tokenName)>=0) {
        V();
        if(findFirstW(t->tokenName)>=0)
            W();
        else return;
    }
    else if(findFirstW(t->tokenName)>=0)
        W();
    else return;
}

void U() {
    if(strcmp(t->tokenName, "(")==0) {
        t = getToken(fptr);
        printToken(t);
        printf("check 102\n");
        if(findFirstS(t->tokenName)>=0) {
            S();
            if(strcmp(t->tokenName, ")")==0) return;
        }
        else {
            invalid(t->tokenName, 1);
        }
    }
    else if(strcmp(t->tokenName, "a")==0) {
        t = getToken(fptr);
        printToken(t);
        printf("check 103\n");
        if(findFirstS(t->tokenName)>=0) {
            S();
            if(strcmp(t->tokenName, "b")==0) return;
        }
        else {
            invalid(t->tokenName, 1);
        }
    }
    else return;
}

void V() {
    t = getToken(fptr);
    printToken(t);
    printf("check 104\n");
    if(findFirstV(t->tokenName)>=0)
        V();
    else return;
}

void W() {
    t = getToken(fptr);
    printToken(t);
    printf("check 105\n");
    if(findFirstW(t->tokenName)>=0)
        W();
    else return;
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
    printf("check 106\n");

    if(findFirstS(t->tokenName)>=0) {
        S();
    }
    else {
        invalid(t->tokenName, 1);
    }

    
    t = getToken(fptr);
    printToken(t);
    printf("check 107\n");
    
    if(!strcmp(t->tokenName, "$")) printf("SUCCESS\n");
    else invalid(t->tokenName, 2);

	displaySymbolTable();
	fclose(fptr);
	return 0;
}