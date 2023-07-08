/* ------------------------------ */
/* -------- DECLARATION: -------- */
/* ------------------------------ */
/*C segments: */
%{
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "../simboltable/hashtable.h"

int yylex();
int yyerror(char *s);

int* date = NULL;
Booked* rooms = NULL;
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

verify:         DATE SEP1 rooms SEP2 books          {date = $1;
                                                     if(date[0] > 0 && date[0] < 13)} ;
                                                     
rooms:          k_room rooms |
                k_room

k_room:         ROOM ARROW NUMBER                   {Room* room = create_room($1,$3);
                                                     insert_room(room); } ;

books:          k_book room_list books | 
                k_book room_list

k_book:         AGENCY MINUS 
                AGCODE MINUS 
                NUMBER MINUS 
                NUMBER MINUS 
                NUMBER MINUS                        {char period[5] = "$7-$9";
                                                     Group* group = create_group($1,$3,$5,period,rooms);
                                                     insert_room(group);} ;

room_list:      PAR_OP book_room PAR_CL             ;

book_room:      ROOM MAJOR NUMBER COMMA book_room 
                | ROOM MAJOR NUMBER                 {Booked* book_room = create_booked($1,$3);
                                                     insert_room(book_room);
                                                     insert_booked(rooms,book_room);} ;


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