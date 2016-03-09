#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//Global variables in C

int **transitions; //transition table
int n_symb;
bool *final; //Final states
char *alphabets;
int state,init_state,num_states;

int new_states,new_init_state;
int **newdfatrans;
bool *new_finals;
bool **group;
int num_groups;



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
	FILE *inp = fopen("dfa.txt","r");
	char word[50],c;
	int i,j,temp,temp2;
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
	while(1)
	{
		c=fgetc(inp);
		if (c=='}')
			break;
		else if(c==',')
		{	
			fscanf(inp," %c ",&alphabets[i++]);
		}
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
/*	printf("\nn_states%d init_state %d\n",num_states,init_state);
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



///////////////////////
int grp(int val) //give the group 
{
    int i,j;
    for(i=0;i<num_groups;i++)
    {
        if(group[i][val]==1)
            return i;
    }
    return -1;
}

void getOptDfaTrans() // give the transitions,final states,initial state for the new dfa
{
    int i,j,temp;
    newdfatrans =(int **)malloc(num_groups*sizeof(int *));
    for(i=0;i<num_groups;i++)
        newdfatrans[i]=(int *)malloc(n_symb*sizeof(int));
    for(i=0;i<num_groups;i++)
        for(j=0;j<n_symb;j++)
            newdfatrans[i][j]=-1;
    new_init_state=grp(init_state); //set new initial state
    //printf("Total no. of states %d\n",num_groups);
    //printf("Initial state = %d\n",new_init_state);
    //set new final states 
    new_finals = (bool *)malloc(num_groups*sizeof(bool));
    memset(new_finals,0,num_groups*sizeof(bool));
    //printf("finalstates {");
    for(i=0;i<num_states;i++)
    {
        if(final[i])
        {
            temp = grp(i);
            new_finals[temp] = true;
            //printf(" %d ",temp);
        }
    }
    //printf("\n transitions \n");
    //build the new transition table for the optDfa
    for(i=0;i<num_groups;i++)
    {
        for(j=0;j<num_states;j++)
            if(group[i][j]==1)
            {
                temp = j;
                break;
            }
        for(j=0;j<n_symb;j++)
        {
            newdfatrans[i][j]=grp(transitions[temp][j]);
      //      printf("%d on seeing %c -> %d \n",i,alphabets[j],newdfatrans[i][j]);
        }
    }
}

int rowToEdit(int i, int g)
{
    if(i==0)
        return g;
    else
        return num_groups+i-1;
}


void split(int g,int *tmp)
{
    int i, j, k=0;
    int tranToGrp[num_states], diffGrps=0;
    bool grpPresent[num_groups];
    //contains groups to which transitions are made
    for(i=0; i<num_groups; i++)
        grpPresent[i]=0;
    //gives the group no. in which the state makes the transition
    for(i=0; i<num_states; i++)
    {
        if(tmp[i]==-1)
            tranToGrp[i]=-1;
        else
        {
            tranToGrp[i]=grp(tmp[i]);
            grpPresent[tranToGrp[i]]=1;
        }
    }
    //no. of groups to be split into
    for(i=0; i<num_groups; i++)
        diffGrps += grpPresent[i];
    
    for(i=0; i<num_groups; i++)
    {
        if(grpPresent[i])
        {
            for(j=0; j<num_states; j++)
            {
                if(tranToGrp[j]==i)
                    group[rowToEdit(k, g)][j]=1;
                
                else if(tranToGrp[j]!=-1)
                    group[rowToEdit(k, g)][j]=0;
            }
            k++;
        }
    }

    num_groups = rowToEdit(k, g);
    
    
}

bool samegrp(int *temp)
{
    int i,j;
    for(i=0;i<num_states;i++)
        for(j=i+1;j<num_states;j++)
            if(temp[i]!=-1 && temp[j]!=-1)
                if(grp(temp[i])!=grp(temp[j]))
                    return false;
    return true;
}

int groupdiv()
{
    int i,j,k;
    int ginit_state;
    int temp[num_states];
    for (i=0;i<num_groups;i++)
    {
        for (j=0;j<num_states;j++)
            if(group[i][j]==true)
            {
                ginit_state=j;
                break;
            }
        for (k=0;k<n_symb;k++)
        {
            for(j=0;j<num_states;j++)
                temp[j]=-1;
            temp[ginit_state]=transitions[ginit_state][k];
            for(j=ginit_state+1;j<num_states;j++)
            {
                if(group[i][j])
                    temp[j]=transitions[j][k];
            }
            
            if(!samegrp(temp))
            {
                split(i,temp); // split the group on the input symbol
                return 0;
            }
        }
    }
    return 1;
}


//write the new dfa to a file
void printdfatofile()
{
    int temp, i, j;
    FILE *fp = fopen("optdfa.txt","w");
    fprintf(fp,"n_states %d\n",num_groups);
    fprintf(fp,"init_state %d\n",new_init_state);
    fprintf(fp,"n_symbols %d\n",n_symb);
    fprintf(fp,"final_state_set { ");
    for(i=0;i<num_groups;i++)
        if(new_finals[i]==true)
        {
            temp=i;
            break;
        }
    fprintf(fp,"%d ",temp);
    for(i=temp+1;i<num_groups;i++)
    {
        if(new_finals[i]==true)
            fprintf(fp,", %d ",i);
    }
    fprintf(fp,"}\n");
    //alphabets
    fprintf(fp,"alphabets { %c ",alphabets[0]);
    for(i=1;i<n_symb;i++)
        fprintf(fp,", %c ",alphabets[i]);
    fprintf(fp,"}\n");
    //transitions
    fprintf(fp,"transition\n");
    for(i=0;i<num_groups;i++)
        for (j=0;j<n_symb;j++)
            if(newdfatrans[i][j]!=-1)
                fprintf(fp,"{ %d , %c ( %d ) }\n",i,alphabets[j],newdfatrans[i][j]);
}

int main()
{
    dfaparse();
    group = (bool **)malloc(num_states * sizeof(bool *));
    int i,j,k,fin;
    for(i=0; i<num_states; i++)
        group[i] = (bool *)malloc(num_states * sizeof(bool));
    
    int temp;
    for(i=0;i<num_states;i++)
        for(j=0;j<num_states;j++)
            group[i][j]=0;
  //  memset(group,0,sizeof(group[0][0])*num_states*num_states);
    //divide into finals and non finals;
    for(i=0;i<num_states;i++)
    {
        if(final[i]==true)
            group[0][i]=true;
        else
            group[1][i]=true;
    }
    num_groups=2;
    fin=0;
    while(!fin)
    {
        fin=groupdiv();
    }
    
    getOptDfaTrans();
    printf("\nDfa optimiztion complete\n");
    printdfatofile();
    return 1;
}