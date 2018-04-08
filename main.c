#include "rdp.h"

int main( void )
{
	char input[50] = {'\0'} ;
	int success = 0 ;
	int i = 0 ;

	success = -1 ;

	printf( " \n\n\t Enter expression : " ) ;
	__fpurge( stdin ) ;
	scanf( "%s" , input ) ;

	success = E( input , &i ) ;

	if( success == 0 )
	{
		printf( " \n\n\t Valid input : %s " , input ) ;
	}
	else
	{
		printf( " \n\n\t Invalid input : %s " , input ) ;
	}

	return 0 ;
}
