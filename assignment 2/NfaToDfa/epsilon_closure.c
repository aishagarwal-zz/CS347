
bool* epsilon_closure(bool *state_set)
{
    bool *final_state_set = (bool *)malloc(n_states*sizeof(bool));
    // if(newstates[i] ==true) then i is the new state.
    int i,n_newstates=0,temp_new_state;
    bool newstates[n_states];
    bool *temp_state_set;
    
    for(i=0;i<n_states;i++)
    {
        final_state_set[i] = state_set[i];
        newstates[i] = false;
        if(final_state_set[i])
        {
            newstates[i] = true;
            n_newstates++;
        }
    }
    while ( n_newstates )
    {
        temp_new_state = -1;
        for( i=0; i<n_states; i++ )
        {
            if ( newstates[i] == true )
            {
                temp_new_state = i;
                newstates[i] = false;
                n_newstates--;
                break;
            }
        }
        if ( temp_new_state != -1 && is_transition (temp_new_state , alpha_to_int("E") ) )
        {
            temp_state_set = transition[temp_new_state][alpha_to_int("E")];
            for(i=0;i<n_states;i++)
            {
                if(temp_state_set[i] && !final_state_set[i])
                {
                    final_state_set[i] = true;
                    newstates[i] = true;
                    n_newstates++;
                }
            }
        }
    }
    
    return final_state_set;
}
