#define EOI     0   /*  End of input */
#define PLUS    1   /*  +            */
#define TIMES   2   /*  *            */
#define LP      3   /*  (            */
#define RP      4   /*  )            */
#define ID      5   /*  identifier   */
#define DOT     6   /*  .            */

extern char *yytext;        /* in lex.c         */
extern int yyleng;
// extern yylineno;
