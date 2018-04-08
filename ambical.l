%{
#include"calc.tab.h"
#include<stdlib.h>	
%}

%%

[0-9]+ { yylval = atoi(yytext) ;
	return NUMBER ;
	}
"+" { return PLUS ; }
"-" { return MINUS ; }
"*" { return MULT ; }
"/" { return DIV ; }
"(" { return OPBR ; }
")" { return CLBR ; }
"\n" { return 0 ; }

%%

int yywrap()
{
	return 1 ;
}


