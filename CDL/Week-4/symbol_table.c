#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_HASH_SIZE 13

struct token {
	char tokenName[100];
	int row, col;
	char type[20];
	int size;
	char returntype[20];
};
//////////////////////////
typedef struct node* Nodeptr;
typedef struct node {
	char lexemeName[100];
	char type[20];
	int size;
	char returntype[20];
	Nodeptr next;
} node;

// Nodeptr mainNode;

Nodeptr hashSymbol[MAX_HASH_SIZE];

int getHashValue(char lexemeName[100]) {
	int sum = 0;
	int i = 0;
	while(lexemeName[i]) {
		sum+=(lexemeName[i]*i);
		i++;
	}
	return (sum%MAX_HASH_SIZE);
}

void displaySymbolTable(){
	printf("\nSymbol table\n< LexemeName, Type, Size, ReturnType>\n\n");
	for(int i=0;i<MAX_HASH_SIZE;i++){
		if(hashSymbol[i] == NULL) {
			// printf("Check %d\n", i);
			continue;
		}
		else{
			Nodeptr cur = hashSymbol[i];
			while(cur){
				printf(" %s\t %s\t %d\t %s\t\n",cur->lexemeName, cur->type, cur->size, cur->returntype);
				cur = cur->next;
			}
		}
	}
}

//searching in the symbol table
int searchSymbolTable(char lexemeName[100], char type[20], char returntype[20]){
	int index = getHashValue(lexemeName);
	if(hashSymbol[index] == NULL){
		// printf("check %d\n", index);
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

void insertSymbolTable(char lexemeName[100], char type[20], char returntype[20]){
	if(searchSymbolTable(lexemeName, type, returntype) == -1){
		Nodeptr n = (Nodeptr)malloc(sizeof(*n));
		// char *str = (char *)calloc(strlen(lexemeName)+1, sizeof(char));
		// strcpy(str, lexemeName);
		strcpy(n->lexemeName, lexemeName);
		n->next = NULL;
		// char *typee = (char *)calloc(strlen(type)+1, sizeof(char));
		// strcpy(typee, type);
		strcpy(n->type, type);
		if(strcmp(type, "int") == 0)
			n->size = 4;
		else if(strcmp(type, "double") == 0)
			n->size = 8;
		else if(strcmp(type, "char") == 0)
			n->size = 1;
		else if(strcmp(type, "float") == 0)
			n->size = 4;
		else
			n->size = 0;
		strcpy(n->returntype, returntype);
		int index = getHashValue(lexemeName);
		// printf("Hash Index %d\n", index);
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

//////////////////////////////////
// struct token* getNode(struct token* tempt) {
// 	struct token* newnode = (struct token*)malloc(sizeof(*newnode));
	// newnode->
// }

FILE *fptr;
char filename[50], buff[50], dbuff[50], c;
int ind = 0;
struct token *t;
int row = 1, col = 1;
int j;
int flag; // for storing the types of variables
// int count = 0;
// char tempbuff[1024];

char keys[32][10] = {"auto", "break", "case", "char", 
					   "const", "continue", "default", "do", 
					   "double", "else", "enum", "extern", 
					   "float", "for", "goto", "if", 
					   "int", "long", "register", "return", 
					   "short", "signed", "sizeof", "static", 
					   "struct", "switch", "typedef", "union", 
					   "unsigned", "while", "volatile", "void"};

char symbol[8][1] = {'[', ']', '(', ')', '{', '}', ',', ';'};

int findSymbol(char ch) {
	for(int i=0; i<8; i++)
		if(symbol[i][0]==ch) return 1;
	return 0;
}

struct token* getToken(FILE* fptr) {
	struct token* newToken = (struct token*)malloc(sizeof(*newToken));
	ind = 0;
	c = fgetc(fptr);
	loop:
		if(c==EOF) return NULL;
		if(c==' ' || c=='\t') {
			while(c==' ' || c=='\t') {
				c=fgetc(fptr);
				col++;
			}
			goto loop;
		}
		if(c == '\n') {
			while(c=='\n') {
				row++;
				c=fgetc(fptr);
			}
			col = 1;
			goto loop;
		}
		if(c=='#') {
			while(c!='\n') {
				c = fgetc(fptr);
				col++;
			}
			row++;
			col = 1;
			c = fgetc(fptr);
			goto loop;
		}
		if(c=='/') {
			c = fgetc(fptr);
			col++;
			if(c=='/') {
				while(c!='\n') {
					c = fgetc(fptr);
					col++;
				}
				row++;
				col = 1;
				c = fgetc(fptr);
			}
			else if(c=='*') {
				while(1) {
					while(c!='*') {
						c = fgetc(fptr);
						col++;
					}
					c = fgetc(fptr);
					col++;
					if(c=='/') break;
					else continue;
				}
				c = fgetc(fptr);
				col++;
			}
			goto loop;
		}
		if(isalpha(c)!=0) {
			newToken->row = row;
			newToken->col = col;
			while(isalpha(c)!=0) {
				buff[ind++] = c;
				col++;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buff[ind]='\0';
			for(j = 0; j<32; j++) {
				if(strcmp(buff, keys[j])==0) {
					strcpy(newToken->tokenName,buff);
					////////////////////////////////////////
					if(strcmp(buff, "char")==0 || strcmp(buff, "double")==0 || strcmp(buff, "float")==0 || strcmp(buff, "int")==0 || strcmp(buff, "void")==0) {
						strcpy(dbuff, buff); // copy the data type
						strcpy(newToken->type, dbuff);
						strcpy(newToken->returntype, dbuff);
						// newToken->size = -1;
						if(strcmp(buff, "char")==0) newToken->size = sizeof(char);
						else if(strcmp(buff, "double")==0) newToken->size = sizeof(double);
						else if(strcmp(buff, "float")==0) newToken->size = sizeof(float);
						else if(strcmp(buff, "int")==0) newToken->size = sizeof(int);
						flag = 1;
					}
					else {
						strcpy(newToken->type, "null");
						strcpy(newToken->returntype, "null");
						newToken->size = -1;
					}
					///////////////////////////////////////
					memset(buff, 0, 50);
					break;
				}
			}
			if(j==32) {
				///////////////////////////////////////
				c = fgetc(fptr);
				fseek(fptr, -1, SEEK_CUR);
				// count++;
				if(flag==1) {
					// printf("\n%s %s\n", buff, dbuff);
					// printf("\n%s\n", dbuff);
					if(c=='(') strcpy(newToken->type, "FUNC");
					else strcpy(newToken->type, dbuff);
					// printf("%s", dbuff);
					strcpy(newToken->returntype, dbuff);
					if(strcmp(dbuff, "char")==0) newToken->size = sizeof(char);
					else if(strcmp(dbuff, "double")==0) newToken->size = sizeof(double);
					else if(strcmp(dbuff, "float")==0) newToken->size = sizeof(float);
					else if(strcmp(dbuff, "int")==0) newToken->size = sizeof(int);
					else newToken->size = 0;
				}
				
				///////////////////////////////////////
				// tempbuff[0]='i';
				// tempbuff[1]='d';
				// char tempc =(count+'0');
			    strcpy(newToken->tokenName, "id");
			    insertSymbolTable(buff, dbuff, dbuff);
				memset(buff, 0, 50);
				if(c==';' || c=='(') {
					memset(dbuff, 0, 50);
					flag = 0;
				}
				// printf("buff<; %s; dbuff; %s\n", buff, dbuff);
				
			}
		}
		else if(isdigit(c)!=0) {
			//////////////
			strcpy(newToken->type, "int");
						strcpy(newToken->returntype, "int");
						newToken->size = sizeof(int);
						////////////////
			newToken->row = row;
			newToken->col = col;
			while(isdigit(c)!=0) {
				buff[ind++] = c;
				col++;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buff[ind]='\0';
			strcpy(newToken->tokenName,"NUM");
			memset(buff, 0, 50);
		}
		else if(findSymbol(c)==1) {
			/////////////
			strcpy(newToken->type, "null");
						strcpy(newToken->returntype, "null");
						newToken->size = -1;
						/////////////
			newToken->tokenName[0] = c;
			newToken->tokenName[1] = '\0';
			newToken->row = row;
			newToken->col = col;
			col++;
		}
		else if(c=='"') {
			/////////////
			strcpy(newToken->type, "int");
						strcpy(newToken->returntype, "int");
						newToken->size = -1;
						/////////////
			newToken->row = row;
			newToken->col = col;
			buff[ind++]=c;
			c = fgetc(fptr);
			col++;
			while(c!='"') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
			}
			buff[ind++]=c;
			buff[ind]='\0';
			col++;
			strcpy(newToken->tokenName, buff);
		}
		else {
			/////////////
			strcpy(newToken->type, "int");
						strcpy(newToken->returntype, "int");
						newToken->size = -1;
						/////////////
			newToken->row = row;
			newToken->col = col;
			if(c=='=') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(c=='=') {
					buff[ind++]=c;
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
				}
				else {
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					fseek(fptr, -1, SEEK_CUR);
				}
 			}
			else if(c=='<'||c=='>'||c=='!') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(c=='=') {
					buff[ind++]=c;
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
				}
				else {
					buff[ind]='\0';
					strcpy(newToken->tokenName,buff);
					col--;
					fseek(fptr, -1, SEEK_CUR);
				}
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*') {
				buff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(buff[ind-1]=='+'||buff[ind-1]=='-') {
					if(c=='+'||c=='=') {
						buff[ind++]=c;
						buff[ind]='\0';
						col++;
						strcpy(newToken->tokenName,buff);
					}
					else if((buff[ind-1]=='+' && c=='+')||buff[ind-1]=='-' && c=='-') {
						buff[ind++]=c;
						buff[ind]='\0';
						col++;
						strcpy(newToken->tokenName,buff);
					}
					else {
						buff[ind]='\0';
						strcpy(newToken->tokenName,buff);
						fseek(fptr, -1, SEEK_CUR);
					}
				}
				else if(buff[ind-1]=='*'||buff[ind-1]=='/') {
					if(c=='=') {
						buff[ind++]=c;
						buff[ind]='\0';
						strcpy(newToken->tokenName,buff);
					}
					else {
						buff[ind]='\0';
						strcpy(newToken->tokenName,buff);
						col--;
						fseek(fptr, -1, SEEK_CUR);
					}
				}
			}
 		}
		return newToken;
}

int main() {
	// mainNode = (Nodeptr)malloc(sizeof(*mainNode));
	for(int i=0; i<MAX_HASH_SIZE; i++)
		hashSymbol[i] == NULL;
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
		printf("<%s, %d, %d, %s, %d, %s>\n", t->tokenName, t->row, t->col, t->type, t->size, t->returntype);
	}
	displaySymbolTable();
	fclose(fptr);
	return 0;
}
