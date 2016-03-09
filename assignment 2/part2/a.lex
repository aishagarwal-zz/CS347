

alpha		[a-zA-Z]
ID       [a-zA-Z_][a-zA-Z0-9]*
DIGIT    [0-9]
NUM     [0-9]+
type    "int"|"char"|"bool"

character "'"."'"

%%

[+*/]|"-"           printf("arithimetic operator printed %s !",yytext);
"<="|">="|"<"|">"|"=="  printf("relational operator %s !",yytext);
"="     printf(" ASSIGN ");
";"     printf(" semi ");
":"     printf(" COLON ");
","     printf(" COMMA ");
"("     printf(" LP ");
")"     printf(" RP ");
{DIGIT} printf(" NUM , %s ",yytext);
"if"    printf(" IF ");    
"then"  printf(" THEN ");
"else"  printf(" ELSE ");
"while" printf(" WHILE ");
"do"    printf(" DO ");
"begin" printf(" BEGIN ");
"end"   printf(" END ");
{type}  printf("type %s",yytext);
"cin"   printf(" CIN ");
"cout"  printf(" COUT ");
{ID}    printf(" ID , %s ",yytext);
"<<"    printf(" LL ");
">>"    printf(" GG ");
{character} printf("char %s",yytext);

.   printf("ERROR TOKEN %s",yytext);

%%

main()
{
  printf("Give me your input:\n");
  yylex();
}

