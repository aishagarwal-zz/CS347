#add paths space seperated directories where it can search for files
VPATH = NfaToDfa

nfa_to_dfa:	nfa_to_dfa.o
			gcc -o $@ $<
			
nfa_to_dfa.o:	nfa_to_dfa.c read_nfa.h epsilon_closure.c epsilon_nfa.txt
				gcc -c $<
				
nfa_clean:	
			rm nfa_to_dfa.o nfa_to_dfa
			
			
#Just for experimenting :P	
hello:	hello.o
#gcc -o hello.exe hello.o
		gcc -o $@ $<
		echo "linking done executable generated"
hello.o:	hello.c
#gcc -c hello.c
			gcc -c $<
			echo "upto assembling done object file generated"
hello_clean:
			rm hello.o hello