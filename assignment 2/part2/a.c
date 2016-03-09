#include<stdio.h>
#include "a.h"

extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

char *names[] = {"EOI","SEMI","PLUS","TIMES","MINUS","DIV","LP","RP","NUM","LT","GT","LTE","GTE","EQU","ASSIGN"
                ,"IF","THEN","ELSE","WHILE","DO","BEGIN1","END","ID","INT","CHAR","BOOL","CIN","COUT","LL","GG"
                , "TRUE", "FALSE", "CHARACTER", "COMMA", "COLON"};

int main(int argc, char *argv[])
{
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
        
    int ntoken;
    ntoken = yylex();
    while(ntoken)
    {
        printf("<%s %s> ",names[ntoken],yytext);
        
        ntoken = yylex();
    }
    printf("EOI\n");
}