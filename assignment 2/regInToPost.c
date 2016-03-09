#include "reg.h"


/*	Following operations are supported
*	a+b denotes a or b
*	a.b denotes concatenation
*	a* denotes zero or more instances of a
*   user may also use parantheses
*/


//return precedence of the operators
int getPrecedence(char c)
{
    switch(c)
    {
        case '(':
            return LP;
            break;
        case '+':
            return PLUS;
            break;
        case '.':
            return DOT;
            break;
        case '*':
            return AST;
            break;
        default:
            return ID;
            break;
    }
}



//convert infix to postfix regex
//assuming correct input regex
void toPostfix()
{
    int l = strlen(reg);
    char post[l];       //contains the ans
    int i=0, j=0, topPrecedence, currPrecedence;
    for(i=0; i<l; i++)
    {
        switch(reg[i])
        {
            case '(':
                push(reg[i]);
                break;
                
            case ')':
                while(top!='(')
                {
                    post[j++]=top;
                    pop();
                }
                pop();
                break;
            
            default:
                while(sz>0)
                {
                    topPrecedence = getPrecedence(top);
                    currPrecedence = getPrecedence(reg[i]);
                    if(topPrecedence >= currPrecedence)
                    {
                        post[j++] = top;
                        pop();
                    }
                    else
                        break;
                }
                push(reg[i]);
                break;
        }
    }
    while(sz>0)
    {
        post[j++] = top;
        pop();
    }

    strcpy(reg, post);
}

//initialize all the global variables
void init()
{
    st[sz] = '\0';
    
    toPostfix();
    
}

int main(int argc, char *argv[])
{
    
	
    char const* const fileName = "regInfix.txt";
    FILE* inp = fopen(fileName, "r");
    
	//read the line which contains the regex
	fgets(reg, sizeof(reg), inp);
	
	//initialize all the global variables
    init();
    FILE* out = fopen("regPostfix.txt", "w+");
	fputs(reg, out);
	fclose(inp);
	fclose(out);
	return 0;
}