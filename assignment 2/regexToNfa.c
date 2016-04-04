#include "reg.h"

int alphaToInt(char c)
{
    if(c=='E')
        return 26;
    return c - 'a';
}


//add transitions and states of n2 to n1
void addTransitions(struct nfa *n1, struct nfa *n2)
{
    int i, j, k;
    //in 1 start adding states after its own
    for(i=n1->nStates; i<n1->nStates + n2->nStates; i++)
    {
        //for every alpha on which transition exists from 2's state
        for(j=0; j<alpha; j++)
        {
            if(n2->tran[i-n1->nStates][j]!=NULL)        //transition on j exists for this state
            {
                n1->tran[i][j] = (bool *)malloc(states * sizeof(bool));
                for(k=0; k<states; k++)
                    n1->tran[i][j][k]=0;
                //add transition for each i, j in 1
                //transitions of 2 will start from k in n1
                for(k=n1->nStates; k<n1->nStates+n2->nStates; k++)
                    n1->tran[i][j][k] = n2->tran[i-n1->nStates][j][k-n1->nStates];
            }
        }
    }
}

//add states of 2 to 1
//update n1->nStates
//add corresponding transitions of 2 to 1
//add E production from final of 1 to start of 2
//replace final of 1 by final of 2
//the start state remains same
void concat(struct nfa *n1, struct nfa *n2)
{
    int i, j;
    addTransitions(n1, n2);
    //add E production from old final of 1 to old start of 2
    for(i=0; i<n1->nStates; i++)
    {
        if(n1->final[i])
        {
            if(n1->tran[i][alphaToInt('E')]==NULL)    //no transition on epsilon exists
            {
                n1->tran[i][alphaToInt('E')] = (bool *)malloc(states * sizeof(bool));
                for(j=0; j<states; j++)
                    n1->tran[i][alphaToInt('E')][j]=0;
                n1->tran[i][alphaToInt('E')][n2->start+n1->nStates]=1;
            }
            else
                n1->tran[i][alphaToInt('E')][n2->start+n1->nStates]=1;
        }
    }
    //replace final of 1 by final of 2
    for(i=0; i<n1->nStates; i++)
        n1->final[i]=0;
    for(i=n1->nStates; i<states; i++)
        n1->final[i]=n2->final[i-n1->nStates];
    //nStates of 1 = nStates of 1 + nStates of 2
    
    n1->nStates += n2->nStates;
    
}

//add epsilon production from final states to start state
//add epsilon production from start state to final states
//no. of states remain same
void iterate(struct nfa *n1)
{
    int i, j;
    for(i=0; i<states; i++)
    {
        if(n1->final[i])
        {
            if(n1->tran[i][alphaToInt('E')]==NULL)    //no transition on epsilon exists
            {
                n1->tran[i][alphaToInt('E')] = (bool *)malloc(states * sizeof(bool));
                for(j=0; j<states; j++)
                    n1->tran[i][alphaToInt('E')][j]=0;
                n1->tran[i][alphaToInt('E')][n1->start]=1;
            }
            else
                n1->tran[i][alphaToInt('E')][n1->start]=1;
        }
    }
    //add epsilon production from start state to final states
    for(i=0; i<states; i++)
    {
        if(n1->final[i])
        {
            if(n1->tran[n1->start][alphaToInt('E')]==NULL)    //no transition on epsilon exists
            {
                n1->tran[n1->start][alphaToInt('E')] = (bool *)malloc(states * sizeof(bool));
                for(j=0; j<states; j++)
                    n1->tran[n1->start][alphaToInt('E')][j]=0;
                n1->tran[n1->start][alphaToInt('E')][i]=1;
            }
            else
                n1->tran[n1->start][alphaToInt('E')][i]=1;
        }
    }
}

//add transitions of 2 to 1
//add new start state to 1
//E productions to initial start states of 1 and 2
//final of 1 = final of 1 + final of 2
//nStates of 1 = nStates of 1 + nStates of 2 + 1
void orOperation(struct nfa *n1, struct nfa *n2)
{
    int i, j;
    addTransitions(n1, n2);

    int oldN1Start=n1->start;
    //change start state of n1
    n1->start=n1->nStates+n2->nStates;
    
    //add new start state to 1
    //E productions to initial start states of 1 and 2
    
    n1->tran[n1->start][alphaToInt('E')] = (bool *)malloc(states * sizeof (bool));
    
    for(i=0; i<states; i++)
        n1->tran[n1->start][alphaToInt('E')][i]=0;
    n1->tran[n1->start][alphaToInt('E')][oldN1Start]=1;
    n1->tran[n1->start][alphaToInt('E')][n2->start+n1->nStates]=1;
    
    //final of 1 = final of 1 + final of 2
    for(i=0; i<states; i++)
        n1->final[i] = n1->final[i];
    for(i=n1->nStates; i<states; i++)
        n1->final[i] = n2->final[i-n1->nStates];
    
    //nStates of 1 = nStates of 1 + nStates of 2 + 1
    n1->nStates = n1->nStates + n2->nStates + 1;
}


//create a nfa which accepts the input char
//two states
//0 is start state
//1 is acc state
//add transition from 0 to 1
void createNfa(struct nfa *n1, char a)
{
    n1->nStates=2;
    n1->start=0;
    int i;
    for(i=0; i<states; i++)
        n1->final[i]=0;
    n1->final[1]=1;
    int j;
    for(i=0; i<states; i++)
        for(j=0; j<alpha; j++)
            n1->tran[i][j]=NULL;
    n1->tran[0][alphaToInt(a)] = (bool *)malloc(states * sizeof(bool));
    for(i=0; i<states; i++)
        n1->tran[0][alphaToInt(a)][i]=0;
    n1->tran[0][alphaToInt(a)][1]=1;
}

//store the output NFA in ans
//from the input postfix regex
void regToNfa()
{
    struct nfa temp[regMaxLen], *temp1;
	int i, l=strlen(reg), j=0;
	
	for(i=0; i<l; i++)
	{
	   if(reg[i]>='a' && reg[i]<='z')
	   {
	        createNfa(&temp[j], reg[i]);
	        nPush(&temp[j++]);
	   }
	   else
	   {
	       switch(reg[i])
	       {
	           case '+':
	                temp1=nTop;
	                nPop();
	                
	                temp[j]=*nTop;
	                nPop();
	                //temp[j]+temp1
	                orOperation(&temp[j], temp1);
	                nPush(&temp[j++]);
	                break;
	           case '.':
	                temp1=nTop;
	                nPop();
	                temp[j]=*nTop;
	                nPop();
	                //temp[j].temp1
	                concat(&temp[j], temp1);
	                nPush(&temp[j++]);
	                break;
	           case '*':
	                temp[j]=*nTop;
	                nPop();
	                //temp1*
	                iterate(&temp[j]);
	                nPush(&temp[j++]);
	                break;
	       }
	   }
	}
}


//print the ans NFA
//as required by manku
void printNfa(struct nfa *ans)
{
    char const* const file = "epsilon_nfa.txt";
    FILE* out = fopen(file, "w+");
    fprintf(out, "nStates %d\n", ans->nStates);
    
    fprintf(out, "initialState %d\n", ans->start);
    
    fprintf(out, "finalStates { ");
    int i, j, k, flag=0;
    for(i=0; i<ans->nStates; i++)
        if(ans->final[i])
        {
            if(flag==0)
                fprintf(out, "%d ", i);
            else
                fprintf(out, ", %d ", i);
        
            flag=1;
        }
    fprintf(out, "}\n");
    
    fprintf(out, "alphabets { ");
    for(i=0; i<alpha-1; i++)
        fprintf(out, "%c , ", 'a'+i);
    fprintf(out, "E }\n");
    
    fprintf(out, "transitions\n");
    for(i=0; i<ans->nStates; i++)
    {
        for(j=0; j<alpha; j++)
        {
            if(ans->tran[i][j]!=NULL)
            {
                fprintf(out, "{ %d ,", i);
                
                char tmp = j+'a';
                if(j==26)
                    tmp='E';
                fprintf(out, "  %c ( ", tmp);
                int nTran=0;
                for(k=0; k<ans->nStates; k++)
                {
                    if(ans->tran[i][j][k])
                    {
                        if(nTran==0)
                            fprintf(out, "%d ", k);
                        else
                            fprintf(out, ", %d ", k);
                        nTran++;
                    }
                }
                fprintf(out, ") }\n");
            }
        }
    }
    fclose(out);
}

int main(int argc, char *argv[])
{
    
    char const* const fileName = "regPostfix.txt";
    FILE* inp = fopen(fileName, "r");
	//read the line which contains the regex in postfix form
	fgets(reg, sizeof(reg), inp);
	
	regToNfa();
	struct nfa *ans;
	ans=nTop;
	printNfa(ans);
	
	fclose(inp);
	return 0;
}