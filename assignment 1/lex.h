#define EOI     0   /* End of input         */
#define SEMI        1   /* ;                */
#define PLUS        2   /* +                */
#define TIMES       3   /* *                */
#define LP      4   /* (                */
#define RP      5   /* )                */
#define NUM   6   /* Decimal Number  */
#define MINUS       7   /*  -   */
#define DIV         8   /*  /   */
#define LT          9   /*  <   */
#define GT          10  /*  >   */
#define ASSIGN          11  /*  :   */
#define COMP        12  /*  =   */
#define IF          13 /*   if      */
#define THEN        14  /* then */
#define WHILE       15 /* while */
#define DO          16 /* do */
#define BEGIN       17 /* begin */
#define END         18 /* end */
#define ID            19 /* identifier */


extern char *yytext;        /* in lex.c         */
extern int yyleng;
extern yylineno;
