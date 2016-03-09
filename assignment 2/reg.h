#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

/*************GLOBAL VARIABLES*************/

#define regMaxLen 256                   //max len of regex
char reg[regMaxLen];                    //contains the regex
                                        //later changed to postfix
#define states 100                      //max no. of states in nfa
#define alpha 27                        //a-z and epsilon as E



//precedence of various operators                            
#define LP 1
#define PLUS 2
#define DOT 3
#define AST 4
#define ID 5


struct nfa
{
    bool *tran[states][alpha];   //a 2D array, each cell points to a bit vector(length = states)
                                 //true entries in the vector denotes possible transitions
    int nStates;
    int start;
    bool final[states];
};

/*******************************************/






/************implement stack for postfix conversion***************/

char st[regMaxLen], top = '\0';
int sz = 0;


void push(char a)
{
    if(sz>=regMaxLen)
        fprintf(stderr, "stack overflow: large regex");
    else
    {
        sz++;
        st[sz] = a;
        top = a;
    }
}

void pop()
{
    if(sz<=0)
        fprintf(stderr, "stack underflow");
    else
    {
        sz--;
        top = st[sz];
    }
}

/*****************************************/





/************implement stack for postfix evaluation***************/

struct nfa *nSt[regMaxLen];
struct nfa *nTop;
int nSz = 0;


void nPush(struct nfa *a)
{
    if(nSz>=regMaxLen)
        fprintf(stderr, "stack overflow: large regex");
    else
    {
        nSz++;
        nSt[nSz] = a;
        nTop = a;
    }
}

void nPop()
{
    if(nSz<=0)
        fprintf(stderr, "stack underflow");
    else
    {
        nSz--;
        nTop = nSt[nSz];
    }
}

/*****************************************/