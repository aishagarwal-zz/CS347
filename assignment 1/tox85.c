#include <string.h>
#include <stdio.h>
#include "lex.h"

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
int if_stck[20],if_stck_top=0,while_stck[20],while_stck_top=0,cond_stck[20],cond_stck_top=0;

char symbol_table[10][10];        //at max 10 varioables, each of length at max 10
                                  //memory locations of the corresponding variables in hex
                                  //range: 02C0H to 02C9H
int table_size=0;                   //no of variables declared uptill now

void hex_print(int num, int bits)
{
    int rem,i;
    char hex[bits];
    char a;
    for(i=0;i<bits;i++)
    {
        rem=num%16;
        if(rem<10)
            a=48+rem;
        else
            a=55+rem;
        hex[i]=a;
        num=num/16;
    }
    for(i=bits-1;i>=0;i--)
        fprintf(fout,"%c",hex[i]);    
    fprintf(fout,"H\n");
}

void if1(int i)
{
    //if ( ti )
    fprintf(fout,"LXI H, 02B%dH\n",i);      //3byte
    fprintf(fout,"MOV A, M\n");             //1byte
    fprintf(fout, "ADI 00H\n");
    fprintf(fout,"JZ xxxxH\n");             //3byte
    if_stck[if_stck_top++]=ftell(fout)-6;
    //printf("offset: %d\n", if_stck[if_stck_top-1]);
    line_no+=9;
}

void endif1()
{
   // printf("%d\n", ftell(fout));
    //printf("offset: %d\n", if_stck[if_stck_top-1]);
    fseek(fout,if_stck[--if_stck_top],SEEK_SET);
    //printf("%d\n", ftell(fout));
    hex_print(line_no, 4);
    fseek(fout,0,SEEK_END);
}

void while_cond()
{
    cond_stck[cond_stck_top++]=line_no;
    
}

void while1(int i)
{
    //while(ti)
    fprintf(fout,"LXI H, 02B%dH\n",i);      //3byte
    fprintf(fout,"MOV A, M\n");             //1byte
    fprintf(fout, "ADI 00H\n");
    fprintf(fout,"JZ xxxxH\n");             //3byte
    while_stck[while_stck_top++]=ftell(fout)-6;
    line_no+=9;
}

void while_end()
{
    fprintf(fout,"JMP ");             //3byte
    hex_print(cond_stck[--cond_stck_top], 4);
    fprintf(fout,"\n");
    line_no+=3;
    
    fseek(fout,while_stck[--while_stck_top],SEEK_SET);
    hex_print(line_no,4);
    fseek(fout,0,SEEK_END);
    
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
    fprintf(fout,"JNZ ");        //3byte
    hex_print(line_no+10,4);
    fprintf(fout,"LXI H, 02B%dH\n",i);    //3byte
    fprintf(fout,"MOV M, A\n");                //1byte
    line_no+=19;
}

//add ti and tj
void plus(int i, int j)
{
    fprintf(fout,"LXI H, 02B%dH\n",j);     //3byte
    fprintf(fout,"MOV B, M\n");           //1byte
    fprintf(fout,"LXI H, 02B%dH\n",i);     //3byte
    fprintf(fout,"MOV A, M\n");           //1byte
    fprintf(fout,"ADD B\n");              //1byte
    fprintf(fout,"STA 02B%dH\n",i);       //3byte
    line_no+=12;
}

// ti -= tj
void minus(int i, int j)
{
    fprintf(fout, "LXI H, 02B%dH\n", j);
    fprintf(fout, "MOV B, M\n");
    fprintf(fout, "LXI H, 02B%dH\n", i);
    fprintf(fout, "MOV A, M\n");
    fprintf(fout, "SUB B\n");
    fprintf(fout, "STA 02B%dH\n", i);
    line_no += 12;
}


void lt(int i, int j)               //strictly <
{
    fprintf(fout, "LXI H, 02B%dH\n", j);
    fprintf(fout, "MOV B, M\n");
    fprintf(fout, "LXI H, 02B%dH\n", i);
    fprintf(fout, "MOV A, M\n");
    //ti <= tj
    fprintf(fout, "SUB B\n");
    fprintf(fout, "MVI A, 00H\n");
    fprintf(fout, "JP ");           //move to STA
    hex_print(line_no+19, 4);
    fprintf(fout, "JZ ");
    hex_print(line_no+19, 4);
    fprintf(fout, "MVI A, 01H\n");
    
    
    fprintf(fout, "STA 02B%dH\n", i);
    line_no += 22;
}

void gt(int i, int j)               //strictly >
{
    fprintf(fout, "LXI H, 02B%dH\n", j);
    fprintf(fout, "MOV B, M\n");
    fprintf(fout, "LXI H, 02B%dH\n", i);
    fprintf(fout, "MOV A, M\n");
    //ti >= tj
    fprintf(fout, "SUB B\n");
    fprintf(fout, "MVI A, 00H\n");
    fprintf(fout, "JM ");           //move to STA
    hex_print(line_no+19, 4);
    fprintf(fout, "JZ ");
    hex_print(line_no+19, 4);
    fprintf(fout, "MVI A, 01H\n");
    fprintf(fout, "STA 02B%dH\n", i);
    line_no += 22;
}

void comp(int i, int j)               
{
    fprintf(fout, "LXI H, 02B%dH\n", j);
    fprintf(fout, "MOV B, M\n");
    fprintf(fout, "LXI H, 02B%dH\n", i);
    fprintf(fout, "MOV A, M\n");
    //ti == tj
    fprintf(fout, "SUB B\n");
    fprintf(fout, "MVI A, 01H\n");
    fprintf(fout, "JZ ");           //move to STA  
    hex_print(line_no+16, 4);
    fprintf(fout, "MVI A, 00H\n");
    fprintf(fout, "STA 02B%dH\n", i);
    line_no += 19;
}

void divi(int i, int j)
{
    //ti = ti/tj
    fprintf(fout, "LXI H, 02B%dH\n", j); 
    fprintf(fout, "MOV B, M        ;Get the dividend in B - reg.\n"); 
    fprintf(fout, "MVI C, 00H      ;Clear C - reg for quotient\n"); 
    fprintf(fout, "LXI H, 02B%dH\n", i);
    fprintf(fout, "MOV A, M        ;Get the divisor in A - reg\n");
    fprintf(fout, "NEXT: CMP B           ;Compare A - reg with register B.\n");
    fprintf(fout, "JC LOOP         ;Jump on carry to LOOP\n"); 
    fprintf(fout, "SUB B           ;Subtract A - reg from B - reg. \n");
    fprintf(fout, "INR C           ;Increment content of register C.\n"); 
    fprintf(fout, "JMP NEXT        ;Jump to NEXT \n");
    //fprintf("LOOP: STA 02B%dH       ;Store the remainder in Memory ", i);
    fprintf(fout, "LOOP: MOV A, C        ;Move Content of C - Reg to A - Reg\n");
    fprintf(fout, "STA 02B%dH        ;Store the quotient in memory \n", i);
    line_no += 23;

}


int assign1(char *sub, int i)
{
    // _id := ti
    //check if id is present in symbol_table
    int j;
    if(table_size==10)
    {
        //max limit of id reached
        fprintf(stderr, "error: can't declare more variables\n");
        return 0;
    }
    for(j=0; j<table_size; j++)
    {
        if(strcmp(sub, symbol_table[j])==0)
        {
            break;         //we have to store value at 02CjH
        }
    }
    strcpy(symbol_table[j], sub);
    table_size++;
    fprintf(fout, "LXI H, 02B%dH\n", i);
    fprintf(fout, "MOV A, M\n");
    fprintf(fout, "STA 02C%dH\n", j);
    line_no += 7;
    return 1;
}

void assign2(int i, int j)
{
     //ti:=tj
    fprintf(fout,"LXI H, 02B%dH\n",j);      //3byte
    fprintf(fout,"MOV B, M\n");             //1byte
    fprintf(fout,"MOV A, B\n");             //1byte
    fprintf(fout,"STA 02B%dH\n", i);        //3byte
    line_no+=8;
}

void assign3(int i, int num)
{
    fprintf(fout,"MVI A, ");                //2byte
    hex_print(num,2);
    fprintf(fout, "\n");
    fprintf(fout,"STA 02B%dH\n", i);        //3byte
    line_no+=5;
}

int assign4(int i, char *sub)
{
    //ti := id
    int j;
    for(j=0; j<table_size; j++)
    {
        // printf("a%sa\n", symbol_table[j]);
        // printf("a%sa\n", sub);
        if(strcmp(sub, symbol_table[j])==0)
        {
            break;         //we have to store value at 02CjH
        }
    }
    if(j == table_size)
    {
        if(table_size == 10)
        {
            printf("table_size exceeded \n");
            return 0;
        }
        strcpy(symbol_table[table_size],sub);
        table_size++;
    }
    
    fprintf(fout, "LXI H, 02C%dH\n", j);
    fprintf(fout, "MOV A, M\n");
    fprintf(fout, "STA 02B%dH\n", i);
    line_no += 7;
    return 1;
}

int check(char *line)
{
    int i, j;
    if(strstr(line, " if ")!=NULL)
    {
        i = *(strstr(line, " if ") + 7) - '0';
        if1(i);
        return IF;
    }
    else if(strstr(line, " while ")!=NULL)
    {
        i = *(strstr(line, " while ") + 10) - '0';
        while1(i);
        return WHILE;
    }
    else if(strstr(line, " endWhile ")!=NULL)
    {
        
        while_end();
        return 100;
    }
    else if(strstr(line, " beginWhile ")!=NULL)
    {
        return 100;
    }
    else if(strstr(line, " beginIf ")!=NULL)
    {
        return 100;         //just some non-zero value
    }
    else if(strstr(line, " endIf ")!=NULL)
    {
        endif1();
        return 100;         //just some non-zero value
    }
    else if(strstr(line, " COND ")!=NULL)
    {
        while_cond();
        return 100;         //just some non-zero value
    }
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
    
    /*  three possible cases
    *   id := ti
    *   ti := tj
    *   ti := num
    *   ti := id
    */
    
        if(line[1] == '_')
        {
            j = *(strstr(line, " := ") + 5) - '0';
            char sub[20];
            
            strncpy(sub, line+1, (strstr(line, " := ") - line - 1) );
            sub[(strstr(line, " := ") - line - 1)]='\0';
            if(assign1(sub, j)==0)
                return EOI;
        }
        else
        {
            i = *(strstr(line, " := ") - 1) - '0';
            if( *(strstr(line, " := ") + 4) == '_' )        //ti "= _id"
            {
                char sub[20], *temp;
                int j=0;
                temp = strstr(line, " := ") + 4;
                while( *temp !=' ' && *temp!='\0')
                {
                    sub[j++]=*temp;
                    temp+=1;
                }
                sub[j]='\0';
                if( assign4(i, sub) ==0)
                    return EOI;
            }
            else if( *(strstr(line, " := ") + 1) == 't')        //ti := tj
            {
                j = *(strstr(line, " := ") + 5) - '0';
                assign2(i, j);
            }
            else                                                //ti := num
            {
                int num=0;
                char *c = strstr(line, " := ") + 4;
                for(; *c!=' '; c++)
                {
                    num *= 10;
                    num += (*c - '0');
                }
                assign3(i, num);
            }
        }
        
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
    while (fgets(line, sizeof(line), inp)) 
    {
        
        fprintf(fout, "  ;%s\n", line);
        // printf("%s\n", line);
        int key = check(line);
        // if(key==PLUS || key==COMP || key==ASSIGN || key==LT || key==GT || key==MINUS || key==TIMES || key==DIV)
        // {
            
        // }
        //printf("%s", line);
        if (key == EOI)
        {
            printf("error in: %s\n", line);
            return 0;
        }
           
        
    }
    
    fprintf(fout, "HLT\n");
    fclose(inp);
    fclose(fout);
    return 0;
}