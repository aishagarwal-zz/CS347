#include "reg.h"


/*	Following operations are supported
*	a+b denotes a or b
*	a.b denotes concatenation
*	a* denotes zero or more instances of a
*   user may also use parantheses
*/



// char checkSt[regMaxLen], checkTop='\0';
// int checkSz=0;
// bool checkPush(char a)
// {
//     if(checkSz>regMaxLen)
//         return 0;
//     else
//     {
//         checkSz++;
//         checkSt[checkSz]=a;
//         top=a;
//         return 1;
//     }
// }
// bool checkPop()
// {
//     if(checkSz<=0)
//         return 0;
//     else
//     {
//         checkSz--;
//         top=checkSt[checkSz];
//         return 1;
//     }
// }

//return 1 if invalid regex
//else return 0
bool isInvalid()
{
    int i, l=strlen(reg), paraBalance=0;
    //check all symbols are valid
    for(i=0; i<l; i++)
        if(reg[i]!='.' && reg[i]!='*' && reg[i]!='+')
            if(reg[i]<'a' && reg[i]>'z')
                return 1;
    
    for(i=0; i<l; i++)
    {
        if(reg[i]=='(')
        {
            paraBalance++;
            
            if(i==l-1)
                return 1;
            if(i!=0)
            {
                if(reg[i-1]!='+' && reg[i-1]!='.')
                    return 1;
            }
            if(i!=l-1)
            {
                if(reg[i+1]<'a' || reg[i+1]>'z')
                    return 1;
            }
        }
        else if(reg[i]==')')
        {
            paraBalance--;
            if(i==0)
                return 1;
            if(i!=0)
            {
                if(reg[i-1]!='*' && (reg[i-1]<'a' || reg[i-1]>'z'))
                    return 1;
            }
            if(i!=l-1)
            {
                if(reg[i+1]!='+' && reg[i+1]!='.' && reg[i+1]!='*')
                    return 1;
            }
        }
        else if(reg[i]>='a' && reg[i]<='z')
        {
            if(i!=0)
            {
                if(reg[i-1]!='(' && reg[i-1]!='+' && reg[i-1]!='.')
                    return 1;
            }
            if(i!=l-1)
            {
                if(reg[i+1]!='+' && reg[i+1]!='.' && reg[i+1]!='*' && reg[i+1]!=')')
                    return 1;
            }
        }
        else if(reg[i]=='+' || reg[i]=='.')
        {
            if(i==0 || i==l-1)
                return 1;
            if(reg[i-1]!='*' && (reg[i-1]<'a' || reg[i-1]>'z') && reg[i-1]!=')')
                return 1;
            if(reg[i+1]!='(' && (reg[i-1]<'a' || reg[i-1]>'z'))
                return 1;
        }
        else if(reg[i]=='*')
        {
            if(i==0)
                return 1;
            if(reg[i-1]!=')' && (reg[i-1]<'a' || reg[i-1]>'z'))
                return 1;
            if(i!=l-1)
                if(reg[i+1]!=')' && reg[i+1]!='+' && reg[i+1]!='.')
                    return 1;
        }
            
            
    }
    if(paraBalance!=0)
        return 1;
    return 0;
}

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
	
	if(isInvalid())
	{
	    fprintf(stderr, "invalid regex\n");
	    return 0;
	}
	
	//initialize all the global variables
    init();
    FILE* out = fopen("regPostfix.txt", "w+");
	fputs(reg, out);
	fclose(inp);
	fclose(out);
	return 0;
}