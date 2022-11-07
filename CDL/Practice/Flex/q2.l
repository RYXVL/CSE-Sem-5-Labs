%{
    #include <stdio.h>
%}

%%

"int"|"char" {printf("KEYWORD - %s", yytext);}
[a-zA-Z]+[0-9a-zA-Z]* {printf("ID - %s", yytext);}
"{"|"}"|"("|")"|";"|","|"." {printf("SYMBOL - %s", yytext);}
"+" | "+=" | "++" | "-" | "-=" | "--" | "/" | "/=" | "*" | "*=" {printf("OPERATORS - %s", yytext);}

%%

void main() {
    yyin = fopen("ip.txt", "r");
    yylex();
}

int yywrap() {
    return 1;
}