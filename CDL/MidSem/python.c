#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_HASH_SIZE 13

struct token {
	char tokenName[50];
	char lexemeName[50];
};

typedef struct node* Nodeptr;
typedef struct node {
	char lexemeName[50];
	Nodeptr next;
} node;

Nodeptr hashSymbol[MAX_HASH_SIZE];

int getHashValue(char lexemeName[50]) {
	int sum = 0;
	int i = 0;
	while(lexemeName[i]) {
		sum+=(lexemeName[i]*i);
		i++;
	}
	return (sum%MAX_HASH_SIZE);
}

void displaySymbolTable(){
	printf("\nSymbol table\n");
	for(int i=0;i<MAX_HASH_SIZE;i++){
		if(hashSymbol[i] == NULL) {
			continue;
		}
		else{
			Nodeptr cur = hashSymbol[i];
			while(cur){
				printf("%s\n",cur->lexemeName);
				cur = cur->next;
			}
		}
	}
}

int searchSymbolTable(char lexemeName[50]){
	int index = getHashValue(lexemeName);
	if(hashSymbol[index] == NULL){
		return -1;
	}
	Nodeptr cur = hashSymbol[index];
	int i = 0;
	while(cur != NULL){
		if(strcmp(lexemeName, cur->lexemeName) == 0)
		return i;
		cur = cur->next;
		i++;
	}
	return -1;
}

void insertSymbolTable(char lexemeName[50]){
	if(searchSymbolTable(lexemeName) == -1){
		Nodeptr n = (Nodeptr)malloc(sizeof(*n));
		strcpy(n->lexemeName, lexemeName);
		n->next = NULL;
		int index = getHashValue(lexemeName);
		if(hashSymbol[index] == NULL){
			hashSymbol[index] = n;
			return;
		}
		Nodeptr cur = hashSymbol[index];
		while(cur->next != NULL)
			cur = cur->next;
		cur->next = n;
	}
}


FILE *fptr;
char filename[50], buff[50], c;
int ind = 0;
struct token *t;

char keys[6][10] = {"if", "elif", "else", "print", "input", "while"};

char symbol[9][1] = {'[', ']', '(', ')', '{', '}', ',', ';', ":"};

int searchKeys(char key[50]) {
	for(int i=0; i<6; i++)
		if(strcmp(key, keys[i])==0) return i;
	return -1;
}

int findSymbol(char ch) {
	for(int i=0; i<9; i++)
		if(symbol[i][0]==ch) return i;
	return -1;
}

struct token* getToken(FILE* fptr) {
	struct token* newToken = (struct token*)malloc(sizeof(*newToken));
	ind = 0;
	c = fgetc(fptr);
	loop:
		if(c==EOF) exit(0);
		if(c==' ' || c=='\t') {
			while(c==' ' || c=='\t') {
				c=fgetc(fptr);
			}
			goto loop;
		}
		if(c == '\n') {
			while(c=='\n') {
				c=fgetc(fptr);
			}
			goto loop;
		}
		if(c=='#') {
			while(c!='\n') {
				c = fgetc(fptr);
			}
			c = fgetc(fptr);
			goto loop;
		}
		if(isalpha(c)!=0) {
			while(isalpha(c)!=0 || isdigit(c)!=0) {
				buff[ind++] = c;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buff[ind]='\0';
			if(searchKeys(buff)>-1) {
				insertSymbolTable(buff);
				strcpy(newToken->lexemeName, buff);
				strcpy(newToken->tokenName, "KEYWORD");
			}
			else if(strcmp(buff, "import")==0 || strcmp(buff, "from")==0) {
				while(c!='\n') c = fgetc(fptr);
				c = fgetc(fptr);
				memset(buff, 0, 50);
				ind = 0;
				goto loop;
			}
			else {
				strcpy(newToken->lexemeName, buff);
				strcpy(newToken->tokenName, "ID");
			}
		}
		else if(isdigit(c)!=0) {
			while(isdigit(c)!=0) {
				buff[ind++] = c;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buff[ind]='\0';
			strcpy(newToken->lexemeName, buff);
			strcpy(newToken->tokenName, "NUM");
			memset(buff, 0, 50);
			ind  = 0;
		}
		else if(findSymbol(c)>-1) {
			newToken->lexemeName[0] = c;
			newToken->lexemeName[1] = '\0';
			strcpy(newToken->tokenName, "SYMBOL");
		}
		else if(c=='"') {
			buff[ind++]=c;
			c = fgetc(fptr);
			while(c!='"') {
				buff[ind++]=c;
				c = fgetc(fptr);
			}
			buff[ind++]=c;
			buff[ind]='\0';
			strcpy(newToken->lexemeName, buff);
			strcpy(newToken->tokenName, "STRING LITERAL");
		}
		else {
			if(c=='=') {
				buff[ind++]=c;
				c = fgetc(fptr);
				if(c=='=') {
					buff[ind++]=c;
					buff[ind]='\0';
					strcpy(newToken->lexemeName,buff);
					strcpy(newToken->tokenName, "OPERATOR");
				}
				else {
					buff[ind]='\0';
					strcpy(newToken->lexemeName,buff);
					strcpy(newToken->tokenName, "OPERATOR");
					fseek(fptr, -1, SEEK_CUR);
				}
 			}
			else if(c=='<'||c=='>'||c=='!') {
				buff[ind++]=c;
				c = fgetc(fptr);
				if(c=='=') {
					buff[ind++]=c;
					buff[ind]='\0';
					strcpy(newToken->lexemeName,buff);
					strcpy(newToken->tokenName, "OPERATOR");
				}
				else {
					buff[ind]='\0';
					strcpy(newToken->lexemeName,buff);
					strcpy(newToken->tokenName, "OPERATOR");
					fseek(fptr, -1, SEEK_CUR);
				}
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*') {
				buff[ind++]=c;
				c = fgetc(fptr);
				if(buff[ind-1]=='+'||buff[ind-1]=='-') {
					if(c=='+'||c=='=') {
						buff[ind++]=c;
						buff[ind]='\0';
						strcpy(newToken->lexemeName,buff);
						strcpy(newToken->tokenName, "OPERATOR");
					}
					else if((buff[ind-1]=='+' && c=='+')||buff[ind-1]=='-' && c=='-') {
						buff[ind++]=c;
						buff[ind]='\0';
						strcpy(newToken->lexemeName,buff);
						strcpy(newToken->tokenName, "OPERATOR");
					}
					else {
						buff[ind]='\0';
						strcpy(newToken->lexemeName,buff);
						strcpy(newToken->tokenName, "OPERATOR");
						fseek(fptr, -1, SEEK_CUR);
					}
				}
				else if(buff[ind-1]=='*'||buff[ind-1]=='/') {
					if(c=='=') {
						buff[ind++]=c;
						buff[ind]='\0';
						strcpy(newToken->lexemeName,buff);
						strcpy(newToken->tokenName, "OPERATOR");
					}
					else {
						buff[ind]='\0';
						strcpy(newToken->lexemeName,buff);
						strcpy(newToken->tokenName, "OPERATOR");
						fseek(fptr, -1, SEEK_CUR);
					}
				}
			}
 		}
		return newToken;
}

int main() {
	for(int i=0; i<MAX_HASH_SIZE; i++)
		hashSymbol[i] = NULL;
	printf("Enter the first file to be opened: ");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if(!fptr) {
		printf("The file does not exist.\n");
		exit(0);
	}
	while(1) {
		t = getToken(fptr);
		if(!t) break;
		printf("<%s, %s>\n", t->lexemeName, t->tokenName);
		if(c==EOF) break;
	}
	displaySymbolTable();
	fclose(fptr);
	return 0;
}
