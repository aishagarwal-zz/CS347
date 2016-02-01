#include <stdio.h>
#include <lex.h>

#define t0 02B0
#define t1 02B1
#define t2 02B2
#define t3 02B3     //696
#define t4 02B4     //697
#define t5 02B5     //698
#define t6 02B6     //699


#define SP 03E7  //Stack pointer  999


int line_no;    //smallest empty memory location
FILE *fout;



void hex_print(int num, int bits)
{
    int rem;
    char hex[bits];
    char a;
    for(i=0;i<bits;i++)
    {
        rem=num%16;
        if(rem<10)
            a=48+rem;
        else
            a=55+temp;
        hex[i]=a;
        num=num/16;
    }
    for(i=bits-1;i>=0;i--)
        fprintf(fout,"%c",hex[i]);    
    fprintf(fout,"H");
}

// multiply ti and tj
void times(int i, int j)      
{
    
    fprintf(fout,"LXI H, 02B%dH\n",i);      //3byte
    fprintf(fout,"MOV B, M\n");             //1byte
    fprintf(fout,"LXI H, 02B%dH\n",j);      //3byte
    fprintf(fout,"MOV C, M\n");             //1byte
    fprintf(fout,"MVI A, 00H\n");           //2byte
    fprintf(fout,"ADD B\n");                //1byte
    fprintf(fout,"DCR C\n");                //1byte
    fprintf(fout,"JNZ ",line_no+10);        //3byte
    hex_print(line_no+10,4);
    fprintf(fout,"\nLXI H, 02B%dH\n",i);    //3byte
    fprintf(fout,"MOV M,A");                //1byte
    line_no+=19;
}

void plus(int i, int j)
{
    fprintf(fout,"LXI H, 02B%dH",j);     //3byte
    fprintf(fout,"MOV B, M");           //1byte
    fprintf(fout,"LXI H, 02B%dH",i);     //3byte
    fprintf(fout,"MOV A, M");           //1byte
    fprintf(fout,"ADD B");              //1byte
    fprintf(fout,"STA 02B%dH",i);       //3byte
    line_no+=12;
}

void minus(int i, int j)
{
    fprintf(fout, "LXI H, 02B%dH", j);
    fprintf(fout, "MOV B, M");
    fprintf(fout, "LXI H, 02B%dH", i);
    fprintf(fout, "MOV A, M");
    fprintf(fout, "SUB B");
    fprintf(fout, "STA 02B%dH", i);
    line_no += 12;
}

void lt(int i, int j)               //<
{
    fprintf(fout, "LXI H, 02B%dH", j);
    fprintf(fout, "MOV B, M");
    fprintf(fout, "LXI H, 02B%dH", i);
    fprintf(fout, "MOV A, M");
    //ti <= tj
    fprintf(fout, "CMP B");
    fprintf(fout, "JC ")
    hex_print(line_no+14, 4);
    fprintf(fout, "MVI A,00H\n");
    fprintf(fout, "MVI A,01H\n");
    fprintf(fout, "STA 02B%dH", i);
    line_no += 19;
}

int check(char *line)
{
    int i, j;
    if(strstr(line, " if ")!=NULL)
        return IF;
    else if(strstr(line, " while ")!=NULL)
        return WHILE;
    else if(strstr(line, " then ")!=NULL)
        return THEN;
    else if(strstr(line, " do ")!=NULL)
        return DO;
    else if(strstr(line, " begin ")!=NULL)
        return BEGIN;
    else if(strstr(line, " end ")!=NULL)
        return END;
    else if(strstr(line, " += ")!=NULL)
    {
        //ti += tj
        //call add(i, j)
        i = *(strstr(line, " += ") - 1) - '0';
        j = *(strstr(line, " += ") + 5) - '0';
        plus(i, j);
        return PLUS;
    }
    else if(strstr(line, " -= ")!=NULL)
    {
        i = *(strstr(line, " -= ") - 1) - '0';
        j = *(strstr(line, " -= ") + 5) - '0';
        minus(i, j);
        return MINUS;
    }
    else if(strstr(line, " *= ")!=NULL)
    {
        i = *(strstr(line, " *= ") - 1) - '0';
        j = *(strstr(line, " *= ") + 5) - '0';
        times(i, j);
        return TIMES;
    }
    else if(strstr(line, " /= ")!=NULL)
    {
        i = *(strstr(line, " /= ") - 1) - '0';
        j = *(strstr(line, " /= ") + 5) - '0';
        divi(i, j);
        return DIV;
    }
    else if(strstr(line, " <= ")!=NULL)
    {
        i = *(strstr(line, " <= ") - 1) - '0';
        j = *(strstr(line, " <= ") + 5) - '0';
        lt(i, j);
        return LT;
    }
    else if(strstr(line, " >= ")!=NULL)
    {
        i = *(strstr(line, " >= ") - 1) - '0';
        j = *(strstr(line, " >= ") + 5) - '0';
        gt(i, j);
        return GT;
    }
    else if(strstr(line, " == ")!=NULL)
    {
        i = *(strstr(line, " == ") - 1) - '0';
        j = *(strstr(line, " == ") + 5) - '0';
        comp(i, j);
        return COMP;
    }
    else if(strstr(line, " := ")!=NULL)
    {
        i = *(strstr(line, " := ") - 1) - '0';
        j = *(strstr(line, " := ") + 5) - '0';
        assign(i, j);
        return ASSIGN;
    }
    else                                //if none of the above is found, error with input code
        return EOI;
}


int main(int argc, char* argv[])
{
    line_no=0;
    if(argc <= 1)
    {
        fprintf(stderr, "filename not provided\n");
        return 0;
    }
    char const* const fileName = argv[1];
    FILE* inp = fopen(fileName, "r");
    fout = fopen("codex85.txt", "w+");
    char line[256];
    
    //read the input file line by line
    while (fgets(line, sizeof(line), file)) 
    {
        int key = check(line);
        // if(key==PLUS || key==COMP || key==ASSIGN || key==LT || key==GT || key==MINUS || key==TIMES || key==DIV)
        // {
            
        // }
        printf("%s", line);
           
        
    }

    fclose(inp);
    fclose(out);
    return 0;
}