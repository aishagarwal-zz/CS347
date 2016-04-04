%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include<string.h>
    void yyerror(char *);
   int lineno=1;
    struct node 
    {
        char name[20];
        int nChilds;
        int isToken;
        char tokValue[20];
        struct node *childs[10];
    };
%}

alpha		[a-zA-Z]
ID       [a-zA-Z_][a-zA-Z0-9]*
DIGIT    [0-9]
NUM     [0-9]+
type    "int"|"char"|"bool"
character "'"."'"

%%

"!"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "NEGATION"); yylval.node1 = newnode; newnode->nChilds=0;  newnode->isToken =1; newnode->isToken =1; return NEGATION; }
"+"        { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "PLUS"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; newnode->isToken =1; return PLUS; }
"-"   { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "MINUS"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; newnode->isToken =1; return MINUS; }
"*"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "TIMES"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return TIMES; }
"/"  { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "DIV"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return DIV; }

"<="    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "LTE"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return LTE; }
">="   { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "GTE"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return GTE; }
"<"     { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "LT"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return LT; }
">"     { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "GT"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return GT; }
"=="   { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "EQU"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return EQU; }

"="     { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "ASSIGN"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return ASSIGN; }

";"     { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "SEMI"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return SEMI; }
":"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "COLON"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return COLON; }
","      { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "COMMA"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return COMMA; }
"("       { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "LP"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return LP; }
")"      { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "RP"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return RP; }

{DIGIT}+ { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue, yytext);  strcpy(newnode->name, "NUM"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return NUM; } 

"if"        { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "IF"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return IF; }
"then"      { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "THEN"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return THEN; }
"else"      { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "ELSE"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return ELSE; }
"while"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "WHILE"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return WHILE; }
"do"     { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "DO"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return DO; }
"begin"   { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "BEGIN1"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return BEGIN1; }
"end"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "END"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return END; }

"int"   { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "INT"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return INT; }
"char"  { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "CHAR"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return CHAR; }
"bool"  { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "BOOL"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return BOOL; }
"VOID"  { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "VOID"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return VOID; }

"true"  { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "TRUE"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return TRUE; }
"false" { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "FALSE"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return FALSE; }

"newnode->isToken =1; return" { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "RETURN"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return RETURN; }
{character} { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "CHARACTER"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return CHARACTER; }   

"return" {struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "RETURN"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return RETURN;}

"cin"   { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "CIN"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return CIN; }
"cout"  { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "COUT"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return COUT; }
{ID}    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "ID"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return ID; }
"<<"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "LL"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return LL; }
">>"    { struct node *newnode = (struct node *)malloc( sizeof(struct node) ); strcpy(newnode->tokValue,yytext); strcpy(newnode->name, "GG"); yylval.node1 = newnode; newnode->nChilds=0;   newnode->isToken =1; return GG; }
[ \t] ;
"\n"    lineno++;
.   { printf("ERROR TOKEN %s",yytext); yyerror("invalid character"); }

%%

int yywrap(void)
{
   return 1;
}
