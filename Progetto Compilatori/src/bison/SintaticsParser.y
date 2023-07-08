/* ------------------------------ */
/* -------- DECLARATION: -------- */
/* ------------------------------ */
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
    int* int_vec;
    char* string;
}
%token <integer> NUMBER 
%token <int_vec> DATE 
%token <string> SEP1 ROOM ARROW SEP2 AGENCY AGCODE MINUS PAR_OP PAR_CL MAJOR COMMA
%start verify


/* ------------------------------ */
/* ------- GRAMMAR RULES: ------- */
/* ------------------------------ */
%% 

verify:         DATE SEP1 rooms SEP2 books          {printf(,"CORRECT!!!");} ;
rooms:          ROOM ARROW NUMBER rooms 
                | %empty                            { } ;
books:          AGENCY MINUS 
                AGCODE MINUS 
                NUMBER MINUS 
                NUMBER MINUS 
                NUMBER MINUS 
                room_list books 
                | %empty                            { } ;
room_list:      PAR_OP book_room PAR_CL             { } ;
book_room:      ROOM MAJOR NUMBER COMMA book_room 
                | ROOM MAJOR NUMBER                 { } ;


%%
/* ------------------------------ */
/* --- AUXILIARIES FUNCTIONS: --- */
/* ------------------------------ */

extern FILE* yyin;
extern FILE* yyout;

int main(int argc, char *argv[]){
    
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2],"w");
    if(argc < 2 && !input_file)
        return 1;

    yyin = input_file;
    yyout = output_file;
    
    if(yyparse() == 0)
        printf("\n\n");
    
    return 0;
}

int yyerror(char *s){
    printf("Semantics error.\nString: %s\n\n", s);
}