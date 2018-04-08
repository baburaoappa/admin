#include<stdio.h>
#include<stdbool.h>

#define MAX 10

bool queen_problem( int array[MAX][MAX] , int n , int row ) ;
int queen_is_safe( int array[MAX][MAX] , int row , int col , int n ) ;
int print_solution( int array[MAX][MAX] , int n ) ;

int main( void )
{
	int array[MAX][MAX] = {{0}} ;
	int n = 0 ;

	bool result = false ;

	printf( " \n\n\t Enter no of queens : " ) ;
	scanf( "%d" , &n ) ;

	result = queen_problem( array , n , 0 ) ;

	if( result == true )
	{
		print_solution( array , n ) ;
	}
	else
	{
		printf( " \n\n\t Solution dosen't exit. " ) ;
	}

	return 0 ;
}

bool queen_problem( int array[MAX][MAX] , int n , int row )
{
	bool ret = false ;

	int flag = 0 ;
	int i = 0 ;

	if( row >= n )
	{
		ret = true ;
	}
	else
	{
		for( i = 0 ; i < n ; i++ )
		{
			if( queen_is_safe( array , row , i , n ) == 1 )
			{
				array[row][i] = 1 ;

				flag = 1 ;

				if( queen_problem( array , n , row+1 ) == false )
				{
					array[row][i] = 0 ;

					flag = 0 ;
				}
				else
				{
					i = n ;
				}
			}
		}

		if( flag == 0 )
		{
			ret = false ;
		}
		else
		{
			ret = true ;
		}
	}

	return ret ;
}

int queen_is_safe( int array[MAX][MAX] , int row , int col , int n )
{
	int ret = 1 ;
	int i = 0 ;
	int j = 0 ;

	for( i = 0 ; i < row ; i++ )
	{
		if( array[i][col] == 1 )
		{
			ret = 0 ;
		}
	}

	for( i = row , j = col ; j >= 0 && i >= 0 ; j-- , i-- )
	{
		if( array[i][j] == 1 )
		{
			ret = 0 ;
		}
	}

	for( i = row , j = col ; j < n && i >= 0 ; j++ , i-- )
	{
		if( array[i][j] == 1 )
		{
			ret = 0 ;
		}
	}

	return ret ;
}

int print_solution( int array[MAX][MAX] , int n )
{
	int i = 0 ;
	int j = 0 ;

	printf( " \n\n\t Solution : \n\n\t " ) ;

	for( i = 0 ; i < n ; i++ )
	{
		for( j = 0 ; j < n ; j++ )
		{
			printf( "%5d" , array[i][j] ) ;
		}

		printf( "\n\n\t" ) ;
	}

	return 0 ;
}