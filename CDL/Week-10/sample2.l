%{
	#include <stdio.h>
%}

%%
[a-zA-Z][a-zA-Z0-9]* printf("Identifier\n");
%%

int main() {
	yyin = fopen("ip.txt", "r");
	yylex();
}

int yywrap() { 
	return 1;
}