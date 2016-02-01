#include "lex.h"
#include <stdio.h>
#include <ctype.h>

char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int lex(void)
{

   static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1)
   {       /* Get the next one         */
      while(!*current )
      {
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!gets(input_buffer))
         {
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
      for(; *current; ++current)
      {
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current )
         {
           case ';':
            return SEMI;
           case '+':
            return PLUS;
           case '-':
            return MINUS;
           case '*':
            return TIMES;
           case '/':
            return DIV;
           case '(':
            return LP;
           case ')':
            return RP;
           case '<':
            return LT;
           case '>':
            return GT;
           case ':':
            return ASSIGN;
           case '=':
            return COMP;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current))
               fprintf(stderr, "Not alphanumeric <%c>\n", *current);
            else
            {
               while(isalnum(*current))
                  ++current;
                  
               yyleng = current - yytext;
               int i;
               for(i=0;i<yyleng;i++)
               {
                   if( !(*(yytext+i)>='0' && *(yytext+i)<='9' ) )
                       break;
               }
               if(i==yyleng)
                   return NUM;
               
               if(yyleng==2)
               {
                   if(strncmp(yytext,"if",2)==0)
                       return IF;
                   else if(strncmp(yytext,"do",2)==0)
                       return DO;
               }
               else if(yyleng==3)
               {
                   if(strncmp(yytext,"end",3)==0)
                       return END;
               }
               else if(yyleng==4)
               {
                   if(strncmp(yytext,"then",4)==0)
                       return THEN;
                       
               }
               else if(yyleng==5)
               {
                   if(strncmp(yytext, "while", 5)==0)
                       return WHILE;
                   else if(strncmp(yytext, "begin", 5)==0)
                       return BEGIN;
               }
               return ID;
            }
            break;
         }
      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token)
{
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void)
{
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}