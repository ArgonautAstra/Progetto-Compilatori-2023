/* ------------------------------ */
/* -------- DECLARATION: -------- */
/* ------------------------------ */
/*C segments:*/
%{
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "../symbol_table/hashtable.h"

extern int yylineno; 
extern void yySerror(const char *s);
int yylex();
int yyerror(const char *s);

Booked* rooms; 
int i = 0;
int days = 0;
int* date = NULL;

int days_month(int month){
    switch (month) {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;
    case 2:
        return 28;
        break;
    default:
        return 31;
        break;
    }
}
%}

/*Options:*/
%define parse.error verbose

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

verify:         DATE                                {date = $1;
                                                     if(date[0] < 1 || date[0] > 12)
                                                        yySerror("Invalid Month");
                                                     days = days_month(date[0]); } 
                SEP1 rooms SEP2 books          
                
rooms:          k_room rooms                        |
                k_room                              ;

k_room:         ROOM ARROW NUMBER                   {Room* room = create_room($1,$3);
                                                     insert_room(room);} ;

books:          k_book books                        | 
                k_book                              ;

k_book:         AGENCY MINUS 
                AGCODE MINUS 
                NUMBER MINUS 
                NUMBER MINUS 
                NUMBER MINUS                        {rooms = calloc(SIZE,sizeof(Booked)); i=0;}
                room_list                           {int period = $9-$7;
                                                     if($7 < 1 || $9 > days)
                                                        yySerror("Days of period exceed (greater or lower) the days of the month");
                                                     if(period < 0)
                                                        yySerror("Days of period are inverted");
                                                     Group* group = create_group($1,$3,$5,period,rooms);
                                                     insert_group(group);} ;

room_list:      PAR_OP book_room PAR_CL             ;

book_room:      k_book_room COMMA book_room         |
                k_book_room                         ;

k_book_room:    ROOM MAJOR NUMBER                   {create_booked(&rooms[i],$1,$3); i++;} ;


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
    
    if(yyparse() == 0){
        print_tot();
        printf("\nParser OK. ");
    }     

    fclose(input_file);
    fclose(output_file);
    
    return 0;
}

int yyerror(const char *s){
    printf("\nSintatic Error on line: %.2d -> Error: %s.", yylineno, s);
    exit(-1);
}