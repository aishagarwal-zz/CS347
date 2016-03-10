/*
1. FOR SUBSET CONSTRUCTION MAX NO. OF DFA STATES IS 100 CAN CHANGE BY dfa_size 
    OR IMPLIMENT MALLOC REALLOC ..




*/

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

///////////function declaration//////////////////
void read_nfa();
bool* epsilon_closure(bool *);
/////////////////////////////////////////////////

/////////////////////////////// GLOBAL VARIABLES FOR NFA//////////
int n_states,init_state;
int n_alphabet;
char alphabet[50][15];
bool ***transition;
bool *fstates_set;
//////////////////////////////////////////////////////////

////////////////////////////// GLOBAL VARS FOR DFA/////////
#define dfa_size 100
int st[dfa_size], top=-1, st_size=dfa_size;

int n_dstates=0;
bool *dstates[dfa_size];
int *dtransition[dfa_size] = {NULL};

//////////////////////////////////////////////////////

/////// STACK st ////
void st_push( int val)
{
    if(top >= st_size - 1)
        printf("Error: stack overflow\n");
    else
        st[++top] = val;
}

int st_pop()
{
    if(top == -1)
    {
        printf("Stack: underflow\n");
        return -1;
    }
    return st[top--];
}

bool st_empty()
{
    if(top == -1)
        return true;
    return false;
}
////////////////////

//return true if state has transition on that symbol
bool is_transition(int state, int symbol)
{
    if(transition[state][symbol] == NULL)
        return false;
    return true;
}

// Gives integer mapping of alphabet or a symbol
int alpha_to_int(char *alpha)
{
    int i;
    for(i=0;i<n_alphabet;i++)
    {
        if(strcmp(alpha, alphabet[i]) == 0)
            break;
    }
    if(i==n_alphabet)
        return -1;
    return i;
}

// return bit vector of states (subset of states) on reading symbol on state.
bool* move(bool *state_set, int symbol)
{
    bool *final_state_set = (bool *)malloc(n_states*sizeof(bool));
    memset( final_state_set, 0, n_states*sizeof(bool) );
    bool *temp_state_set;
    
    int i,j;
    for(i=0;i<n_states;i++)
    {
        
        if(state_set[i] == true && is_transition(i,symbol))
        {
            temp_state_set = transition[i][symbol];
            for(j=0;j<n_states;j++)
            {
                final_state_set[j] |= temp_state_set[j];
            }
        }
        
    }
    return final_state_set;
}

// check if state is present in dstates
int present( bool * state)
{
    int i,j;
    for(i=0;i<n_dstates;i++)
    {
        for(j=0;j<n_states;j++)
        {
            if(dstates[i][j] != state[j] )
                break;
        }
        if(j == n_states)
            return i;
    }
    return -1;
}

/* If after move and epsilon closure no state is found then in bool vector all 0's.
    then In DFA there will be a special state error where all 0's and on all symbol transition to itself.
*/
void subset_construction()
{
    int temp_dstate,i,j,k;
    
    bool init[n_states];
    memset(init, 0, n_states*sizeof(bool));
    bool *temp, *temp2;
    init[init_state] = true;
    temp = epsilon_closure(init);   // NOTE: temp is pointing to heap memory.
    dstates[n_dstates++] = temp;              // No need to malloc as it's done in epsilon closure.
    st_push(0);

    while( !st_empty() )
    {
        temp_dstate = st_pop();
        // n_alphabet -1 => last is epsilon we dont want that
        for(i=0;i<n_alphabet-1; i++)
        {
            temp = move( dstates[temp_dstate] , i);
            temp2 = epsilon_closure( temp );
            
            // printf("\nmove %d %d ", temp_dstate, i);
            // for(j=0;j<n_states;j++)
            //     printf("%d ",temp[j]);
            free(temp);
            j=present(temp2);
            if( j == -1 )
            {
                dstates[n_dstates++] = temp2;
                
                if(dtransition[temp_dstate] == NULL)
                {
                    dtransition[temp_dstate] = (int *) malloc( (n_alphabet-1)*sizeof(int) );
                    for(j=0;j<n_alphabet-1;j++)
                        dtransition[temp_dstate][j] = -1;
                }
                dtransition[temp_dstate][i] = n_dstates-1;      // [dfa_state][symbol] => new dfa state 
                //printf("\n dtransition  is %d %s %d  ", temp_dstate, alphabet[i], n_dstates-1);
                st_push(n_dstates -1);
            }
            else
            {
                if(dtransition[temp_dstate] == NULL)
                {
                    dtransition[temp_dstate] = (int *) malloc( (n_alphabet-1)*sizeof(int) );
                    for(k=0;k<n_alphabet-1;k++)
                        dtransition[temp_dstate][k] = -1;
                }
                dtransition[temp_dstate][i] = j;
                //printf("\n dtransition  is %d %s %d ", temp_dstate, alphabet[i], j);
                
            }
            
        }
        
    }
    
}

#include"epsilon_closure.c"
#include"read_nfa.c"

int main()
{
    int i,j;
    read_nfa();
    subset_construction();
    
    /*printf("subset_construction completed\n");
    
    printf("dfa states\n");
    for(i=0;i<n_dstates;i++)
    {
        for(j=0;j<n_states;j++)
            printf("%d ",dstates[i][j]);
        printf("\n");
    }
    printf("dfa transition\n");
    for(i=0;i<n_dstates;i++)
        for(j=0;j<n_alphabet-1;j++)
            printf(" %d %s %d\n",i,alphabet[j],  dtransition[i][j]);
    */
    FILE *fp = fopen("dfa.txt","w");
    fprintf(fp,"n_states %d\n",n_dstates);
    fprintf(fp,"initial_state 0\n");
    
    fprintf(fp, "n_symbol %d\n", n_alphabet-1 );
    fprintf(fp,"final_state_set { ");
    for(i=0;i<n_dstates;i++)
    {
        if(fstates_set[0] == true && dstates[i][0] == true)
            {
                fprintf(fp,"%d ",i);
                
            }
        for(j=1;j<n_states;j++)
        {
            if(fstates_set[j] == true && dstates[i][j] == true)
            {
                fprintf(fp,", %d ",i);
                break;
            }
        }
    }
    fprintf(fp,"}\n");
    
    ////////// alphabets
    fprintf(fp,"alphabets { ");
    
    fprintf(fp,"%s ",alphabet[0]);
    for(i=1;i<n_alphabet-1;i++)
    fprintf(fp,", %s ",alphabet[i]);
    fprintf(fp, "}\n");
    ///// transition
    fprintf(fp,"transition\n");
    for(i=0;i<n_dstates;i++)
    {
        if( dtransition[i] == NULL)
            continue;
        for(j=0;j<n_alphabet-1;j++)
        {
            if(dtransition[i][j] != -1)
            {
                fprintf(fp, "{ %d , %s ( %d ) }\n", i, alphabet[j], dtransition[i][j]);
            }
        }
    }
    
    /* test case
    bool *ans,test_state[3]={0};
    test_state[1]=1;
    
    int i,sym = 0;
    ans=move(test_state,sym);
    ans=epsilon_closure(ans);
    printf("\n\n move test\n");
    for(i=0;i<3;i++)
        printf("%d ",ans[i]);
    */
    
    
    // free heap memory
    free(fstates_set);
    free(transition);
    fclose(fp);
    return 0;
}