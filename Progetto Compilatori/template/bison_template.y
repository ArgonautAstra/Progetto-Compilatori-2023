/* -------------------- */
/* --- DECLARATION: --- */
/* -------------------- */
/*Tokens:*/

%start assiome
%token PIU MENO PER DIV

/*Typing:*/

%union {
    int integer;
    float floating;
}
%type <floating> expr value

/*Precedences:*/

%left PIU MENO
%left PER DIV

/*C segments: */

%{
    
    
%}

/*Options: */

%option noyywrap

%% 
/* ---------------------- */
/* --- GRAMMAR RULES: --- */
/* ---------------------- */

assiome: expr               {printf("Risultato: %d\n", $1)}

expr:    expr PIU expr      {$$ = $1 + $3;}    |
         expr MENO expr     {$$ = $1 - $3;}    |
         expr PER expr      {$$ = $1 * $3;}    |
         expr DIV expr      {$$ = $1 / $3;}    |
         value              {$$ = $1;}         ;

value:   value              {$$ = $1;}         ;


%%
/* ------------------------------ */
/* --- AUXILIARIES FUNCTIONS: --- */
/* ------------------------------ */

int main(int argc, char *argv[]){

    yyparse();
    
    return 0;
}

yyerror(char *s){
    printf("Semantics error.\n");
}