void dfaparse()
{
    //printf("%s",filename);
	FILE *inp = fopen("dfa.txt","r");
	char word[50],c;
	int num_states,i,j,temp,temp2;
	fscanf(inp,"%s %d",word,&num_states);
	printf("%s %d",word,num_states);
	fscanf(inp,"%s %d",word,&init_state);
	printf("%s %d",word,init_state);
	fscanf(inp,"%s %d",word,&n_symb);
	printf("%s %d",word,n_symb);
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
	printf("\nn_states%d init_state %d\n",num_states,init_state);
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
    }
    fclose(inp);
}