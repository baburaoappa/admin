%{
# include <stdio.h>
# include <stdlib.h>
%}
%token NUMBER
%left PLUS MINUS
%left MULT DIV
%left OPBR CLBR
%%
S : E
{
printf ("\n\t Result = %d \n", $1) ;
}
;
E : E PLUS E { $$ = $1 + $3 ; }
  | E MINUS E { $$ = $1 - $3 ; }
  | E MULT E { $$ = $1 * $3 ; }
  | E DIV E {
if ($3 == 0)
{
yyerror("\n\t Division by zero \n") ;
yyerrok ; //error recovery ie.suspend the program
}
else
{
$$ = $1 / $3 ;
}
}
| OPBR E CLBR
{ $$ = $2 ; }  //x=(5)
| NUMBER { $$ = $1 ; }  //assign result
;
%%
int main(void)
{
printf ("\n\t Enter expression = ") ;
yyparse() ; //returns 0 if grammar is correct and returns 1 if input it passes is incorrect. it does not separate tokens 
return 0 ;
}
int yyerror(char *msg)
{
printf ("%s", msg) ;
exit(0) ;
}

