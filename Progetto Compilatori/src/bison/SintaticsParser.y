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
%token <string> DATE SEP1 ROOM ARROW SEP2 AGENCY AGENCY_CODE BOOK SPACE
%start verify

/*Precedences:*/

%% 
/* ---------------------- */
/* --- GRAMMAR RULES: --- */
/* ---------------------- */
verify:     DATE SEP1 rooms SEP2 books  {printf(" FINITO");} ;
rooms:      ROOM ARROW NUMBER rooms | %empty         {printf(" STANZE");} ;
books:      AGENCY SPACE AGENCY_CODE SPACE NUMBER SPACE NUMBER SPACE NUMBER SPACE BOOK books | %empty         {printf(" PRENOTAZIONI");} ;


%%
/* ------------------------------ */
/* --- AUXILIARIES FUNCTIONS: --- */
/* ------------------------------ */

extern FILE* yyin;

int main(int argc, char *argv[]){
    
    if(argc < 2)
        return 1;
    
    FILE* input_file = fopen(argv[1], "r");

    if(!input_file)
        return 1;

    yyin = input_file;
    
    if(yyparse() == 0)
        printf("\n\n");
    
    return 0;
}

int yyerror(char *s){
    printf("Semantics error. String: %s\n", s);
}