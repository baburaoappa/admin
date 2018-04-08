%{
#include<stdio.h>
#include<stdlib.h>
%}

%token NUMBER
%left PLUS MINUS
%left MULT DIV
%left OPBR CLBR

%%

S : E { printf("\n\t Result = %d\n\n",$1) ;
      }
;

E : E PLUS T { $$ = $1 + $3 ;
	     }
| E MINUS T { $$ = $1 - $3 ;
	    }	
| T { $$ = $1 ;
    }
;

T : T MULT F { $$ = $1 * $3 ;
	     }
| T DIV F { 
		if($3 == 0)
		{
			yyerror("Division by 0!") ;
			yyerrok;
		}
		else
		{
			$$ = $1 / $3 ;
		}
	  }
| F { $$ = $1 ;
    }
;

F : NUMBER { $$ = $1 ; }
| OPBR E CLBR { $$ = $2 ; }
;

%%

int main(void)
{
	printf("\n ********** CALCULATOR **********\n") ; 
	printf("\n Enter the expression : ") ;
	yyparse();
	return 0 ;
}

int yyerror(char *msg)
{
	printf("\n\n\t %s",msg) ;
	exit(0) ;
}

