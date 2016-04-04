yacc -d b.y;
lex b.lex;
gcc y.tab.c lex.yy.c -o b;
./b;