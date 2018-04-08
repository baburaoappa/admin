/*
 * rdp.c
 *
 *  Created on: 31-Mar-2018
 *      Author: dell
 */
#include "rdp.h"

int E( char ic[10] , int *i )
{
	int success = 0 ;

	success = -1 ;

	success = T( ic , &(*i) ) ;

	if( success == 0 )
	{
		success = Edash( ic , &(*i) ) ;
	}

	return success ;
}

int T( char ic[10] , int *i )
{
	int success = 0 ;

	success = -1 ;

	success = F( ic , &(*i) ) ;

	if( success == 0 )
	{
		*i = *i + 1 ;

		success = Tdash( ic , &(*i) ) ;
	}

	return success ;
}

int F( char ic[10] , int *i )
{
	int success = 0 ;

	success = -1 ;

	if( ic[*i] == '(' )
	{
		success = -1 ;

		*i = *i + 1 ;

		success = E( ic , &(*i) ) ;

		if( success == 0 )
		{
			success = -1 ;

			if( ic[*i] == ')' )
			{
				success = 0 ;
			}
			else
			{
				success = -1 ;
			}
		}
	}
	else
	{
		if( ic[*i] == 'm' )
		{
			success = 0 ;
		}
	}

	return success ;
}

int Edash( char ic[10] , int *i )
{
	int success = 0 ;

	success = -1 ;

	if( ic[*i] == '+' )
	{
		*i = *i + 1 ;

		success = T( ic , &(*i) ) ;

		if( success == 0 )
		{
			success = Edash( ic , &(*i) ) ;
		}
	}
	else
	{
		success = 0 ;
	}

	return success ;
}

int Tdash( char ic[10] , int *i )
{
	int success = 0 ;

	success = -1 ;

	if( ic[*i] == '*' )
	{
		*i = *i + 1 ;

		success = F( ic , &(*i) ) ;

		if( success == 0 )
		{
			*i = *i + 1 ;

			success = Tdash( ic , &(*i) ) ;
		}
	}
	else
	{
		success = 0 ;
	}

	return success ;
}
