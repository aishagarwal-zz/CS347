%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    int yylex(void);
    extern int lineno;
    void yyerror(char *);
    
    struct node
    {
        char name[20];
        int nChilds;
        int isToken;
        char tokValue[20];
        struct node *childs[10];
    };
    void updateChild(struct node *newNode, struct node *$1, struct node *$2, struct node *$3, struct node *$4, struct node *$5, struct node *$6, struct node *$7, struct node *$8, struct node *$9, struct node *$10);
    struct node * errorNode();
    struct node *root;
    
    struct node *bfs[500];
    int start=0, end=0;
    void push(struct node *n);
    
    struct node *pop();
    
%}

%start S1


%union 
{
    struct node *node1;
}

%token < node1> NEGATION
%token < node1> PLUS
%token < node1> MINUS
%token < node1> TIMES
%token < node1> DIV

%token < node1> LTE
%token < node1> GTE
%token < node1> LT
%token < node1> GT 
%token < node1> EQU

%token < node1> ASSIGN
%token < node1> SEMI
%token < node1> COMMA
%token < node1> COLON
%token < node1> LP  
%token < node1> RP

%token < node1 > NUM

%token < node1> IF   
%token < node1> THEN
%token < node1> ELSE
%token < node1> WHILE
%token < node1> DO
%token < node1> BEGIN1
%token < node1> END

%token < node1> INT
%token < node1> BOOL
%token < node1> CHAR
%token < node1> VOID

%token < node1> TRUE
%token < node1> FALSE


%token < node1> CHARACTER
%token < node1> CIN
%token < node1> COUT
%token < node1> ID
%token < node1> LL
%token < node1> GG

%token < node1> RETURN

%type < node1 >  S1, S func_decl func_defn semi stmt datatype opt_arg_list func_type arg_list arg func_stmt rt expr stmt_list colon opt_else opt_stmt_list var_decl func_call io else_stmt expr1 rel operator expr2 add_sub expr3 mul_div term id_list opt_expr_list expr_list

%%

S1 : S  {printf("S1 : S\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "S1");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode; root=$$;} 
    ;

S : 
      func_defn  S    {  printf("S : func_defn S\n");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "S");    newNode->nChilds=1; updateChild(newNode, $1, NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;} 
    |  func_decl semi    S       {  printf("S : func_decl SEMI S\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "S");    newNode->nChilds=3; updateChild(newNode, $1, $2, $3, NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
    |  stmt    S         {  printf("S : stmt S\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "S");    newNode->nChilds=2; updateChild(newNode, $1, $2, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}   
    | /* epsilon */       {  printf("S : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "S");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode; }
    ;

func_decl :
            datatype ID LP opt_arg_list RP         {  printf("func_decl : func_type ID LP opt_arg_list RP\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_decl");    newNode->nChilds=5; updateChild(newNode, $1, $2, $3, $4, $5,  NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            ;
            
func_type : VOID                {  printf("func_type : VOID\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_type");    newNode->nChilds=1; updateChild(newNode, $1, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            | datatype          {  printf("func_type : datatype\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_type");    newNode->nChilds=1; updateChild(newNode, $1, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            ;
            
opt_arg_list :
                arg_list        {  printf("opt_arg_list : arg_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_arg_list");    newNode->nChilds=1; updateChild(newNode, $1, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
                | /*        */  {  printf("opt_arg_list : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_arg_list");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode;}
                ;
                
arg_list :
            arg COMMA arg_list  {  printf("arg_list : arg COMMA arg_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "arg_list");    newNode->nChilds=3; updateChild(newNode, $1, $2, $3, NULL,NULL,NULL,NULL,NULL,NULL, NULL); $$=newNode;}
            | arg               {  printf("arg_list : arg\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "arg_list");    newNode->nChilds=1; updateChild(newNode, $1, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            ;
            
arg :               
    datatype ID                 {  printf("arg : datatype ID\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "arg");    newNode->nChilds=2; updateChild(newNode, $1, $2, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
    ;

func_defn :
            func_decl BEGIN1 func_stmt END      {   printf("func_defn : func_decl BEGIN1 func_stmt END\n");    struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_defn");    newNode->nChilds=4; updateChild(newNode, $1, $2, $3, $4, NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            ;
            
func_stmt :
            stmt func_stmt                      {   printf("func_stmt : stmt func_stmt\n");    struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_stmt");    newNode->nChilds=2; updateChild(newNode, $1, $2, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            | RETURN rt semi                    {   printf("func_stmt : RETURN rt semi\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_stmt");    newNode->nChilds=3; updateChild(newNode, $1, $2, $3, NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            | /*    */                          {   printf("func_stmt : epsilon\n");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_stmt");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode; }
            ;
            
rt :
     expr                                       {   printf("rt : expr\n");   struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "rt");    newNode->nChilds=1; updateChild(newNode, $1, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode; }
    |   /*      */                              {   printf("rt : epsilon\n");   struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "S");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode;}
    ;


/* change semi not required */
stmt_list :                         
            stmt stmt_list          {  printf("stmt_list : stmt stmt_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt_list");    newNode->nChilds=2; updateChild(newNode, $1, $2, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;}
            | stmt                  {  printf("stmt_list : stmt\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt_list");    newNode->nChilds=1; updateChild(newNode, $1, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL); $$=newNode;} 
            ;


stmt :  
        ID colon ASSIGN expr semi           {  printf("stmt : ID COLON ASSIGN expr semi\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=5; updateChild(newNode, $1, $2, $3, $4, $5, NULL,NULL,NULL,NULL,NULL); $$=newNode;}
        |   IF expr THEN stmt opt_else      {  printf("stmt : IF expr THEN stmt opt_else\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=5; updateChild(newNode, $1, $2, $3, $4, $5, NULL,NULL,NULL,NULL,NULL); $$=newNode;}
        |   WHILE expr DO stmt              {  printf("stmt : WHILE expr DO stmt\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=4; newNode->childs[0]=$1;newNode->childs[1]=$2;newNode->childs[2]=$3;newNode->childs[3]=$4; $$=newNode;}
        |   BEGIN1  opt_stmt_list END       {  printf("stmt : BEGIN1  opt_stmt_list END\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=3; newNode->childs[0]=$1;newNode->childs[1]=$2;newNode->childs[2]=$3; $$=newNode;}
        |   var_decl semi                   {  printf("stmt : var_decl semi\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        |   func_call semi                  {  printf("stmt : func_call semi\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        |   io semi                         {  printf("stmt : io semi\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "stmt");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        ;


opt_else : 
            else_stmt                       {  printf("opt_else : else_stmt\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_else");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode;}
            |   /* Just comment Epsilon production */ { printf("opt_else : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_else");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode;    }
            ;
            
else_stmt :
            ELSE stmt_list              {  printf("else_stmt : ELSE stmt_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "else_stmt");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode; }
            ;


expr : 
        expr1 rel           {  printf("expr : expr1 rel\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        | LP expr RP        {  printf("expr : LP expr RP\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr");    newNode->nChilds=3; newNode->childs[0]=$1;newNode->childs[1]=$2;newNode->childs[2]=$3; $$=newNode;}
        ;
        
rel :
        operator expr       {  printf("rel : operator expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "rel");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        | /*    */          {  printf("rel : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "rel");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode;}
        ;

operator :
            LTE             {  printf("operator : LTE\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "operator");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode;}
            |   GTE         {  printf("operator : GTE\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "operator");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode;}
            |   EQU         {  printf("operator : EQU\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "operator");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode;}
            |   GT          {  printf("operator : GT\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "operator");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode;}
            |   LT          {  printf("operator : LT\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "operator");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode;}
            ;

expr1 :
        expr2 add_sub       {  printf("expr1 : expr2 add_sub\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr1");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode; }
        ;

add_sub : 
        PLUS expr           {  printf("add_sub : PLUS expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "add_sub");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        | MINUS expr        {  printf("add_sub : MINUS expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "add_sub");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        | /*    */          {  printf("add_sub : epsilon\n");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "add_sub");    newNode->nChilds=1; newNode->childs[0] =NULL; $$=newNode;}
        ;

expr2 : 
        expr3 mul_div       {  printf("expr2 : expr3 mul_div\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr2");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode; }
        ;
        
mul_div :   
        TIMES expr          {  printf("mul_div : TIMES expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "mul_div");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        | DIV expr          {  printf("mul_div : DIV expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "mul_div");    newNode->nChilds=2; newNode->childs[0]=$1; newNode->childs[1]=$2; $$=newNode;}
        | /*    */          {  printf("mul_div : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "mul_div");    newNode->nChilds=1; newNode->childs[0] = NULL; $$=newNode;}
        ;

expr3 : 
        NEGATION expr       {  printf("expr3 : NEGATION expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr3");    newNode->nChilds=2; newNode->childs[0]=$1;newNode->childs[1]=$2; $$=newNode;}
        |   term            {  printf("expr3 : term\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr3");    newNode->nChilds=1; newNode->childs[0]=$1; $$=newNode; }
        ;
term :
        ID                  {  printf("term : ID\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "term");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode; }
        |   NUM             {  printf("term : NUM\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "term");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode; } 
        |   func_call       {   printf("term : func_call\n");   struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "term");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}       /*added new production*/
        |   CHARACTER       {   printf("term : CHARACTER\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "term");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}          /*added new production*/
        ;
        
opt_stmt_list : stmt_list           {  printf("opt_stmt_list : stmt_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_stmt_list");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
                | /* epsilon */     {  printf("opt_stmt_list : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_stmt_list");    newNode->nChilds=1; newNode->childs[0]=NULL; $$=newNode;}
                ;

var_decl : 
            datatype id_list        {  printf("var_decl : datatype id_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "var_decl");    newNode->nChilds=2; newNode->childs[0] = $1; newNode->childs[1] = $2; $$=newNode;}
            ;

id_list : 
            ID COMMA id_list        {  printf("id_list : ID COMMA id_list \n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "id_list");    newNode->nChilds=3; newNode->childs[0] = $1; newNode->childs[1] = $2; newNode->childs[2]=$3;  $$=newNode;}
            | ID                    {  printf("id_list : ID\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "id_list");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
            ;
            
datatype : 
            INT                     {  printf("datatype : INT\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "datatype");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
            | BOOL                  {  printf("datatype : BOOL\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "datatype");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode; }
            | CHAR                  {  printf("datatype : CHAR\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "datatype");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
            ;

func_call :
            ID LP opt_expr_list RP  {  printf("func_call : ID LP opt_expr_list RP\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "func_call");    newNode->nChilds=4; newNode->childs[0] = $1; newNode->childs[1]=$2; newNode->childs[2]=$3; newNode->childs[3] = $4; $$=newNode;}
            ;
            
opt_expr_list : expr_list           {  printf("opt_expr_list : expr_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_expr_list");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
                | /*    epsilon */  {  printf("opt_expr_list : epsilon\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "opt_expr_list");    newNode->nChilds=1; newNode->childs[0] = NULL; $$=newNode;}
                ;
                
expr_list : expr COMMA expr_list    {  printf("expr_list : expr COMMA expr_list\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr_list");    newNode->nChilds=3; newNode->childs[0] = $1; newNode->childs[1]= $2; newNode->childs[2]=$3; $$=newNode;}
            | expr                  {  printf("expr_list : expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "expr_list");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
            ;   

io : CIN GG ID                      {  printf("io : CIN GG ID\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "io");    newNode->nChilds=3; newNode->childs[0] = $1; newNode->childs[1] = $2; newNode->childs[2] = $3; $$=newNode;}
    
    | COUT LL expr                  {   printf("io : COUT LL expr\n"); struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "io");    newNode->nChilds=3; newNode->childs[0] = $1; newNode->childs[1] = $2; newNode->childs[2] = $3; $$=newNode;}     /*added new expression*/
    ;

colon :
        COLON           {  printf("colon : COLON\n");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "colon");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}       
        | error      {  yyerror("colon missing ");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "colon");    newNode->nChilds=1; newNode->childs[0] = errorNode(); $$=newNode;}   
        ;
semi :
        SEMI            {  printf("semi : SEMI\n");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "semi");    newNode->nChilds=1; newNode->childs[0] = $1; $$=newNode;}
    /*    | error      {  yyerror("semicolon missing ");  struct node *newNode = (struct node *)malloc(sizeof(struct node)); newNode->isToken=0;  strcpy(newNode->name, "semi");    newNode->nChilds=1; newNode->childs[0] = errorNode(); $$=newNode;}  */
        ;
/*
program:
        program expr '\n'         { printf("%d\n", $2); }
        | 
        ;

expr:
        INTEGER                   { $$ = $1; }
        | expr '+' expr           { $$ = $1 + $3; }
        | expr '-' expr           { $$ = $1 - $3; }
        ;
*/

%%

void yyerror(char *s) {
    fprintf(stderr, "ERROR: %s at line no. %d\n", s, lineno );
}


void updateChild(struct node *newNode, struct node *a, struct node *b, struct node *c, struct node *d, struct node *e, struct node *f, struct node *g, struct node *h, struct node *i, struct node *j)
    {
        int n=newNode->nChilds;
        if(n>=1)
            newNode->childs[0]=a;
        if(n>=2)
            newNode->childs[1]=b;
        if(n>=3)
            newNode->childs[2]=c;
        if(n>=4)
            newNode->childs[3]=d;
        if(n>=5)
            newNode->childs[4]=e;
        if(n>=6)
            newNode->childs[5]=f;
        if(n>=7)
            newNode->childs[6]=g;
        if(n>=8)
            newNode->childs[7]=h;
        if(n>=9)
            newNode->childs[8]=i;
        if(n>=10)
            newNode->childs[9]=j;
        
    }

    
    
struct node *errorNode()
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->name, "error");
    newNode->nChilds=0;
    
}

void push(struct node *n)
{
    bfs[start]=n;
    start++;
    start%=500;
    
}
struct node *pop()
{
    int temp=end;
    end = (++end)%500;
    return bfs[temp];
}

printTree(struct node *root)
{
    FILE *fp = fopen("treeOut.txt", "w+");
    push(root);
    int next_nodes=1,i,j,curr_nodes=1;
    struct node *temp;
    while(start !=end)
    {
        curr_nodes = next_nodes;
        next_nodes = 0;
        for(j=0;j<curr_nodes;j++)
        {
            temp = pop();
            if(temp == NULL)
            {
                fprintf(fp, " epsilon ");
                continue;
            }
            else if( strcmp( temp -> name, "error") == 0 )
                fprintf(fp, " (error production) ");
            else if( temp->nChilds == 1 && temp->childs[0] == NULL )
            {
                fprintf(fp, " %s ( %d ) ", temp->name, temp->nChilds);
                
            }
            else if(temp -> isToken)
                fprintf(fp, "%s value: %s ( %d ) ", temp->name, temp->tokValue, temp->nChilds);
            else
                fprintf(fp, "%s ( %d ) ", temp->name, temp->nChilds);
            next_nodes += temp->nChilds;
            for(i=0; i<temp->nChilds; i++)
            {
                push(temp->childs[i]);
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


int main(void) {
    yyparse();
    
    printTree(root);
    return 0;
}
