%{
	int chars = 0;
	int words = 0;
	int lines = 0;
%}

id [a-zA-Z_][a-zA-Z0-9_]*

%%
[a-zA-Z]+ { words++; chars += strlen(yytext); }
\n { chars++; lines++; }
. { chars++; }
%%

main(int argc, char **argv) {
	yyin = fopen("ip.txt", "r");
	yylex();
	printf("%d %d %d\n", lines, words, chars); 
}
int yywrap() {
	return 1;
}