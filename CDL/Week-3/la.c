#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct token {
	char tokenName[100];
	int row, col;
};

FILE *fptr;
char filename[50], buffff[50], c;
int ind = 0;
struct token *t;
int row = 1, col = 1;
int j;

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
		if(c==EOF) exit(0);
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
				buffff[ind++] = c;
				col++;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buffff[ind]='\0';
			for(j = 0; j<32; j++) {
				if(strcmp(buffff, keys[j])==0) {
					strcpy(newToken->tokenName,buffff);
					memset(buffff, 0, 50);
					break;
				}
			}
			if(j==32) {
			    strcpy(newToken->tokenName,buffff);
				memset(buffff, 0, 50);
			}
		}
		else if(isdigit(c)!=0) {
			newToken->row = row;
			newToken->col = col;
			while(isdigit(c)!=0) {
				buffff[ind++] = c;
				col++;
				c = fgetc(fptr);
			}
			fseek(fptr, -1, SEEK_CUR);
			buffff[ind]='\0';
			strcpy(newToken->tokenName,buffff);
			memset(buffff, 0, 50);
		}
		else if(findSymbol(c)==1) {
			newToken->tokenName[0] = c;
			newToken->tokenName[1] = '\0';
			newToken->row = row;
			newToken->col = col;
			col++;
		}
		else if(c=='"') {
			newToken->row = row;
			newToken->col = col;
			buffff[ind++]=c;
			c = fgetc(fptr);
			col++;
			while(c!='"') {
				buffff[ind++]=c;
				c = fgetc(fptr);
				col++;
			}
			buffff[ind++]=c;
			buffff[ind]='\0';
			col++;
			strcpy(newToken->tokenName, buffff);
		}
		else {
			newToken->row = row;
			newToken->col = col;
			if(c=='=') {
				buffff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(c=='=') {
					buffff[ind++]=c;
					buffff[ind]='\0';
					strcpy(newToken->tokenName,buffff);
				}
				else {
					buffff[ind]='\0';
					strcpy(newToken->tokenName,buffff);
					fseek(fptr, -1, SEEK_CUR);
				}
 			}
			else if(c=='<'||c=='>'||c=='!') {
				buffff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(c=='=') {
					buffff[ind++]=c;
					buffff[ind]='\0';
					strcpy(newToken->tokenName,buffff);
				}
				else {
					buffff[ind]='\0';
					strcpy(newToken->tokenName,buffff);
					col--;
					fseek(fptr, -1, SEEK_CUR);
				}
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*') {
				buffff[ind++]=c;
				c = fgetc(fptr);
				col++;
				if(buffff[ind-1]=='+'||buffff[ind-1]=='-') {
					if(c=='+'||c=='=') {
						buffff[ind++]=c;
						buffff[ind]='\0';
						col++;
						strcpy(newToken->tokenName,buffff);
					}
					else {
						buffff[ind]='\0';
						strcpy(newToken->tokenName,buffff);
						fseek(fptr, -1, SEEK_CUR);
					}
				}
				else if(buffff[ind-1]=='*'||buffff[ind-1]=='/') {
					if(c=='=') {
						buffff[ind++]=c;
						buffff[ind]='\0';
						strcpy(newToken->tokenName,buffff);
					}
					else {
						buffff[ind]='\0';
						strcpy(newToken->tokenName,buffff);
						col--;
						fseek(fptr, -1, SEEK_CUR);
					}
				}
			}
 		}
		return newToken;
}

int main() {
	printf("Enter the first file to be opened: ");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if(!fptr) {
		printf("The file does not exist.\n");
		exit(0);
	}
	while(1) {
		t = getToken(fptr);
		printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col);
	}
	fclose(fptr);
	return 0;
}