#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct token {
	char tokenName[100];
	int row, col;
};

FILE *fptr;
char filename[50], buff[50], c;
int ind = 0;
struct token t;
int row = 1, col = 1;

struct token getToken(FILE* fptr) {
	struct token newToken;
	char keys[32][10] = {"auto", "break", "case", "char", 
					   "const", "continue", "default", "do", 
					   "double", "else", "enum", "extern", 
					   "float", "for", "goto", "if", 
					   "int", "long", "register", "return", 
					   "short", "signed", "sizeof", "static", 
					   "struct", "switch", "typedef", "union", 
					   "unsigned", "while", "volatile", "void"};
	c = fgetc(fptr);
	if(c==EOF) exit(0);
	// for row and col - check after correct output return
	// if(c=='\n') {
	// 	col++;
	// 	row = 1;
	// }
	// else row++;

	// skips all preprocessor directives
	if(c=='#')
		while(c!='\n')
			c = fgetc(fptr);
	// skips all comments
	if(c=='/') {
		c = fgetc(fptr);
		if(c=='/')
			while(c!='\n')
				c = fgetc(fptr);
		else if(c=='*')
			while(1) {
				while(c!='*')
					c = fgetc(fptr);
				c = fgetc(fptr);
				if(c=='/') break;
				else continue;
			}
	}
	while(isalpha(c)==1) {
		buff[ind++] = c;
		c = fgetc(fptr);
	}
	buff[ind]='\0';
	for(int j = 0; j<32; j++) {
		if(strcmp(buff, keys[j])==0) {
			strcpy(newToken.tokenName,"Keyword");
			newToken.row = newToken.col = 123;
			// fputc('\n', fptr2);
			break;
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
	t = getToken(fptr);
	while(t.tokenName!=EOF) {
		printf("<%s, %d, %d>", t.tokenName, t.row, t.col);
		t = getToken(fptr);
	}
	// getToken(fptr);
	fclose(fptr);
	return 0;
}
