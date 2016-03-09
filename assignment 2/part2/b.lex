%{
#include "a.h"
%}

alpha		[a-zA-Z]
ID       [a-zA-Z_][a-zA-Z0-9]*
DIGIT    [0-9]
NUM     [0-9]+
type    "int"|"char"|"bool"
character "'"."'"

%%

"+"   return PLUS;
"-"   return MINUS;
"*"   return TIMES;
"/"   return DIV;

"<="  return LTE;
">="  return GTE;
"<"   return LT;
">"   return GT;
"=="  return EQU;

"="     return ASSIGN ;

";"     return SEMI;
":"     return COLON;
","     return COMMA;
"("     return LP;
")"     return RP;

{DIGIT}+ return NUM; 

"if"    return IF;    
"then"  return THEN;
"else"  return ELSE;
"while" return WHILE;
"do"    return DO;
"begin" return BEGIN1;
"end"   return END;

"int"   return INT;
"char"  return CHAR;
"bool"  return BOOL;
"true"  return TRUE;
"false" return FALSE;
{character} return CHARACTER;

"cin"   return CIN;
"cout"  return COUT;
{ID}    return ID;
"<<"    return LL;
">>"    return GG;
[ \t\n] ;
.   printf("ERROR TOKEN %s",yytext);

%%

int yywrap(void)
{
  return 1;
}
