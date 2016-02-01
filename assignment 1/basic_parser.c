/* Basic parsePr, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.h"

statements()
{
    /*  stmt → id := expr
             | if expr then stmt
             | while expr do stmt
             | begin opt_stmts end
    */
    if( match( ID ) )
    {
        advance();
        if( match( ASSIGN ) )
        {
            advance();
            if( match(COMP) )
            {
                advance();
                expression();
                if( match(SEMI) )
                    advance();
                else
                    fprintf( stderr, "%d: semi missing and i am adding\n", yylineno );
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
        expression();
        if( match( THEN ) )
        {
            advance();
            if( !match(EOI) )
                statements();
        }
        else
            fprintf( stderr, "%d: then missing\n", yylineno );
    }
    else if( match(WHILE) )
    {
        advance();
        expression();
        if( match( DO ) )
        {
            advance();
            if( !match(EOI) )
                statements();
        }
        else
            fprintf( stderr, "%d: DO missing\n", yylineno );
    }
    else if( match(BEGIN) )
    {
        advance();
        if( !match(EOI) )
            opt_stmts();
        if( match( END ) )
        {
            advance();
        }
        else
            fprintf( stderr, "%d: END missing\n", yylineno );
    }
    else
        fprintf( stderr, "%d: syntax error id or if or while or begin expected \n", yylineno );

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
expression()
{
    /* expression -> term expression' */

    term();
    expr_prime();
}

expr_prime()
{
    /* expression' -> PLUS term expression'
                    | MINUS term expression'
                    | LT term expression'
                    | GT term expression'
                    | COMP term expression'
     *              | epsilon
     */

   
    if( match( PLUS ) )
    {
        advance();
        term();
        expr_prime();
    }
    if( match( MINUS ) )
    {
        advance();
        term();
        expr_prime();
    }
    if( match( LT ) )
    {
        advance();
        term();
        expr_prime();
    }
    if( match( GT ) )
    {
        advance();
        term();
        expr_prime();
    }
    if( match( COMP ) )
    {
        advance();
        term();
        expr_prime();
    }
    
}

term()
{
    /* term -> factor term' */

    factor();
    term_prime();
}

term_prime()
{
    /* term' -> TIMES factor term'
             |   DIV factor term'
     *       |   epsilon
     */

    if( match( TIMES ) )
    {
        advance();
        factor();
        term_prime();
    }
    if( match( DIV ) )
    {
        advance();
        factor();
        term_prime();
    }
}

factor()
{
    /* factor   ->    NUM_OR_ID
     *          |     LP expression RP
     */

    if( match(NUM) || match(ID) )
        advance();

    else if( match(LP) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
       fprintf( stderr, "%d Number or identifier expected\n", yylineno );
}
