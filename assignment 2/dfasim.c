#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* Global Variables */

int **transitions; //transition table
int n_symb;
bool *final; //Final states
char *alphabets;
int state,init_state,num_states;

//parse the dfa
int alpha_to_int(char alpha)
{
	int i;
	for(i=0;i<n_symb;i++)
	{
		if(alpha==alphabets[i])
			break;
	}
	if(i==n_symb)
		return -1;
	return i;
}

void dfaparse()
{
    //printf("%s",filename);
	FILE *inp = fopen("optdfa.txt","r");
	char word[50],c;
	int num_states,i,j,temp,temp2;
	fscanf(inp,"%s %d",word,&num_states);
//	printf("%s %d",word,num_states);
	fscanf(inp,"%s %d",word,&init_state);
//	printf("%s %d",word,init_state);
	fscanf(inp,"%s %d",word,&n_symb);
//	printf("%s %d",word,n_symb);
	//read final states
	final = (bool *)malloc(num_states*sizeof(bool));
	memset(final,0,num_states*sizeof(bool));
	fscanf(inp,"%s %s %d",word,word,&temp);
	if (temp==125)
	{
		printf("No final state in the DFA\n");
		return;
	}
	else
		final[temp]=true;
	while(1)
	{
		c = fgetc(inp);
		if (c == '}')
			break;
		else if(c == ',')
		{
			fscanf(inp," %d ",&temp);
			final[temp]=true;
		}
	}
	//read alphabets
	alphabets = (char *)malloc(n_symb*sizeof(char));
	fscanf(inp,"%s %s",word,word);
	i=0;
	fscanf(inp," %c ",&alphabets[i++]);
//	printf("%c ,",alphabets[i-1]);
	while(1)
	{
		c=fgetc(inp);
		if (c=='}')
			break;
		else if(c==',')
		{	
			fscanf(inp," %c ",&alphabets[i++]);
//				printf("%c ,",alphabets[i-1]);
		}
//		printf("\n");
	}

	//read transitions
	transitions = (int**)malloc(num_states*sizeof(int *));
	for(i=0;i<num_states;i++)
		transitions[i]=(int *)malloc(n_symb*sizeof(int));
	for(i=0;i<num_states;i++)
		for (j = 0; j < n_symb; j++)
			transitions[i][j]= -1;
	fscanf(inp,"%s",word);
	while(fscanf(inp,"%s",word)!=EOF)
	{
		fscanf(inp," %d ",&temp);
		int symb;
		fscanf(inp," , %c ",&c);
		symb = alpha_to_int(c);
		fscanf(inp," %s ",word);
		fscanf(inp," %d ",&temp2);
		if(transitions[temp][symb]!=-1)
		{
			printf("Error in defining DFA.One state cannot have two transitions on the same symb\n");
			return;
		}
		else 
			transitions[temp][symb]=temp2;
		c=fgetc(inp);
		if(c==',')
		{
			printf("incorrect input dfa\n");
			return;
		}
		fscanf(inp,"%s",word);
	}
	/*printf("\nn_states%d init_state %d\n",num_states,init_state);
    printf("final states \n");
    for(i=0;i<num_states;i++)
        printf("%d ",final[i]);
    printf("\nalphabets\n");
    for(i=0;i<n_symb;i++)
        printf("%c\n", alphabets[i]);
    printf("transitions\n");
    for(i=0;i<num_states;i++)
    {
        for(j=0;j<n_symb;j++)
        {
            printf("state: %d symbol: %c -> ",i,alphabets[j]);
            if(transitions[i][j] == -1)
                printf("NULL");
            else
            {
                printf("%d ",transitions[i][j]);
            }
            printf("\n");
        }
    }*/
    fclose(inp);
}
//simulate the dfa
int dfasim(char c)
{
	int i,cur_symb,j;
	j = n_symb;
	for (i=0;i<j;i++)
	{
		if (c==alphabets[i])
		{
			cur_symb = i;
			break;
		}
	}
	if (i==j)
	{
		printf("Unknown symbol found\n");
		return 0;
	}

	else if (transitions[state][cur_symb]!= -1)
	{
	    printf("%d on seeing %c ->",state,c);
		state = transitions[state][cur_symb];
		printf("%d \n",state);
		return 1;
	}
	else
	{
		printf("incorrect transition found\n");
		return 0;
	}
}

int main(int argc,char *argv[])
{
	char temp[6],c;
	int i=0;
	char str[50];
	//size_t len = 0;
	//ssize_t read;
	int res=0,sim1;
	printf("\nEnter the input string:");
	scanf("%s",str);
	dfaparse();
	state = init_state;
	for(i=0;i<strlen(str);i++)
	{
		sim1=dfasim(str[i]);
		if(sim1==0)
			break;
	}
	if(sim1==0)
	{
		printf("String does not lie in the grammar\n");
		return -1;
	}
	if (final[state]==1)
		res = 1;
	
	//if the last state is final state or not
	if (res==1)
		printf("This string belongs to the grammar this DFA is simulating\n");
	else 
		printf("String does not lie in the grammar\n");
	return 0;
}