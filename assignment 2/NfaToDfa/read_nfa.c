
void read_nfa()
{
    FILE *inp = fopen("epsilon_nfa.txt", "r");
    char word[50], c;
    int temp,temp2,i,j;
    fscanf(inp, "%s %d", word, &n_states);
    fscanf(inp, "%s %d", word, &init_state);
    
    fstates_set = (bool *) malloc(n_states*sizeof(bool));
    memset(fstates_set,0,n_states*sizeof(bool));
    
    // read set of final states
    fscanf(inp, "%s %s %d", word, word, &temp);
    fstates_set[temp] = true;
    while(1 )
    {
        c= fgetc(inp);
        if(c == '}')
            break;
        if(c == ',')
        {
            fscanf(inp,"%d",&temp);
            fstates_set[temp] = true;
        }
    }
    
    // read alphabets
    n_alphabet = 0;
    fscanf(inp,"%s %s",word,word);
    fscanf(inp,"%s",alphabet[n_alphabet++]);
    while(1)
    {
        c= fgetc(inp);
        if(c == '}')
            break;
        if(c == ',')
            fscanf(inp,"%s",alphabet[n_alphabet++]);
    }
    
    // read transition
    transition = (bool ***) malloc( n_states * sizeof(bool **) );
    for( i=0; i<n_states; i++ )
        transition[i] = (bool **) malloc( n_alphabet * sizeof(bool *) );
    for(i=0;i<n_states;i++)
        for(j=0;j<n_alphabet;j++)
            transition[i][j] = NULL;
    
    fscanf(inp, "%s",word);     // read transition
    while(fscanf(inp, "%s",word) != EOF)   // while we get '{'
    {
        fscanf(inp, "%d ,", &temp);  // state
        fscanf(inp, "%s", word);    // symbol
        int symbol = alpha_to_int(word);
        
        transition[temp][symbol] = (bool *) malloc( n_states* sizeof(bool) );
        
        fscanf(inp, "%s", word);    // read '('
        fscanf(inp, "%d", &temp2);   // first final state
        transition[temp][symbol][temp2] = true;
        
        while(1)
        {
            c= fgetc(inp);
            if(c == ')')
                break;
            if(c == ',')
            {
                fscanf(inp, "%d", &temp2);
                transition[temp][symbol][temp2] = true;
            }
        }
        fscanf(inp, "%s",word);     // read '}'
        
    }
    
    printf("\nn_states%d init_state %d\n",n_states,init_state);
    printf("final states \n");
    for(i=0;i<n_states;i++)
        printf("%d ",fstates_set[i]);
    printf("alphabets\n");
    for(i=0;i<n_alphabet;i++)
        printf("%s\n", alphabet[i]);
    printf("transitions\n");
    for(i=0;i<n_states;i++)
    {
        for(j=0;j<n_alphabet;j++)
        {
            printf("state: %d symbol: %s -> ",i,alphabet[j]);
            if(transition[i][j] == NULL)
                printf("NULL");
            else
            {
                for(temp=0;temp<n_states;temp++)
                    printf("%d ",transition[i][j][temp]);
            }
            printf("\n");
        }
    }
    fclose(inp);
}