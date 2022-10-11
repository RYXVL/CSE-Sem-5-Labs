%{
	#include <stdio.h>
	int vowels = 0;
	int consonants = 0;
%}

%%
[a,b,c,d,e,A,E,I,O,U] {vowels++;}
[a-zA-Z] {consonants++;}
%%

int main() {
	yyin = fopen("ip.txt", "r");
	yylex();
	printf("%d %d", vowels, consonants);
}

int yywrap() { 
	return 1;
}
