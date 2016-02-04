#include <stdio.h>
#include "lex.h"

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );

extern char *newname( void       );
extern void freename( char *name );

statements()
{
    /*  statements -> expression SEMI  |  expression SEMI statements  */

    char *tempvar,*yytext_temp;
    int yyleng_temp;
    
    if( match( ID ) )
    {
        yyleng_temp=yyleng;
        yytext_temp=yytext;
        advance();
        if( match( ASSIGN ) )
        {
            advance();
            if( match(COMP) )
            {
                advance();
                tempvar=expression();
                //print the assignment
                printf("	_%0.*s := %s \n", yyleng_temp, yytext_temp,tempvar );
                if( match(SEMI) )
                    advance();
                else
                    fprintf( stderr, "%d: semi missing and i am adding\n", yylineno );
                freename( tempvar );
            }
            else
                fprintf( stderr, "%d: comp char missing\n", yylineno );
            
                
        }
        else
            fprintf( stderr, "%d: assign char missing\n", yylineno );    
        
    } 
    
    else if( match( IF ) )
    {
        advance();
        
        tempvar=expression();
        printf("     if ( %s ) \n", tempvar);
        if( match( THEN ) )
        {
            printf("     then \n  beginIf \n");
            advance();
            if( !match(EOI) )
                statements();
            printf("     endIf \n");
        }
        else
            fprintf( stderr, "%d: then missing\n", yylineno );
        freename( tempvar );
    }
    
    
    else if( match(WHILE) )
    {
        advance();
        printf("     COND \n");
        tempvar=expression();
        printf("     while ( %s ) \n", tempvar);
        if( match( DO ) )
        {
            printf("     do \n    beginWhile \n");
            advance();
            if( !match(EOI) )
                statements();
            // fprintf(stdout, "yolo\n");
            printf("     endWhile \n");
        }
        else
            fprintf( stderr, "%d: DO missing\n", yylineno );
        freename( tempvar );
    }
    
    else if( match(BEGIN) )
    {
        printf("     begin \n");
        advance();
        if( !match(EOI) )
            opt_stmts();
        if( match( END ) )
        {
            printf("    end \n");
            advance(); 
        }
        else
            fprintf( stderr, "%d: END missing\n", yylineno );
    }
    
    else
    {
        //show error and skip the current lexeme
        fprintf( stderr, "%d: syntax error id or if or while or begin expected \n", yylineno );
        advance();
    }
    
}


opt_stmts()
{
    /*
        opt_stmts → stmt_list |є
    */
    if(!match(END))
        stmt_list();
    
}

stmt_list()
{
    /*
        stmt_list → stmt_list; stmt | stmt
    */
    statements();
    if(!match(END))
        stmt_list();   
}

char    *expression()
{
    /* expression -> term expression'
     * expression' -> PLUS term expression' |  epsilon
     */

    char  *tempvar, *tempvar2;

    tempvar = term();
    while(match(PLUS) || match(MINUS) || match(LT) || match(GT) || match(COMP))
    {
        
        if( match( PLUS ))
        {
            advance();
            tempvar2 = term();    
            printf("     %s += %s \n", tempvar, tempvar2 );
        }
        if( match( MINUS ) )
        {
            advance();
            tempvar2 = term();
            printf("     %s -= %s \n", tempvar, tempvar2 );
        }
        if( match( LT ) )
        {
            advance();
            tempvar2 = term();
            printf("     %s <= %s \n", tempvar, tempvar2 );
        }
        if( match( GT ) )
        {
            advance();
            tempvar2 = term();
            printf("     %s >= %s \n", tempvar, tempvar2 );
        }
        if( match( COMP ) )
        {
            advance();
            tempvar2 = term();
            printf("     %s == %s \n", tempvar, tempvar2 );
        }
        freename( tempvar2 );
    }
    return tempvar;
}

char    *term()
{
    char  *tempvar, *tempvar2 ;

    tempvar = factor();
    while( match( TIMES ) || match(DIV) )
    {
        if(match(TIMES))
        {
            advance();
            tempvar2 = factor();
            printf("     %s *= %s \n", tempvar, tempvar2 );
            freename( tempvar2 );
        }
        else
        {
             advance();
            tempvar2 = factor();
            printf("     %s /= %s \n", tempvar, tempvar2 );
            freename( tempvar2 );
        }
        
    }
    

    return tempvar;
}

char    *factor()
{
    char *tempvar;

    if( match(NUM))
    {
    /* Print the assignment instruction. The %0.*s conversion is a form of
     * %X.Ys, where X is the field width and Y is the maximum number of
     * characters that will be printed (even if the string is longer). I'm
     * using the %0.*s to print the string because it's not \0 terminated.
     * The field has a default width of 0, but it will grow the size needed
     * to print the string. The ".*" tells printf() to take the maximum-
     * number-of-characters count from the next argument (yyleng).
     */
     

        printf("    %s := %0.*s \n", tempvar = newname(), yyleng, yytext );
        advance();
    }
    else if( match(ID) )
    {
        printf("    %s := _%0.*s \n", tempvar = newname(), yyleng, yytext );
        advance();
    }
    else if( match(LP) )
    {
        advance();
        tempvar = expression();
        if( match(RP) )
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    }
    else
       fprintf( stderr, "%d: Number or identifier expected\n", yylineno );

    return tempvar;
}