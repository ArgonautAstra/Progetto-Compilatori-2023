/* -------------------- */
/* --- DECLARATION: --- */
/* -------------------- */
/*C segments: */

%{
#include <stdio.h>
#include <stdlib.h> 

int yylex();
int yyerror(char *s);
%}

/*Token with Type:*/

%union{
    int integer;
    char* string;
}
%token <integer> NUMBER 
%token <string> DATA SEP1 ROOM ARROW SEP2 AGENCY AGENCY_CODE BOOK SPACE
%start verify

/*Precedences:*/

%% 
/* ---------------------- */
/* --- GRAMMAR RULES: --- */
/* ---------------------- */
verify:     DATA    {printf("avà dai");} ;


%%
/* ------------------------------ */
/* --- AUXILIARIES FUNCTIONS: --- */
/* ------------------------------ */

int main(int argc, char *argv[]){

    printf("FUNZIONO!!!\n");
    
    if(yyparse() == 0)
        printf("boh");
    
    return 0;
}

int yyerror(char *s){
    printf("Semantics error.\n");
}