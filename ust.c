
#include<stdio.h>
#include<string.h>
#include<ctype.h>

struct TERM
{
	int index ;
	char symbol[10] ;
	char class[10] ;
};

struct UST
{
	int index ;
	int lineno ;
	char lexeme[10] ;
	char class[10] ;
	int no ;
};

struct IDTAB
{
	int index ;
	char identifier[10] ;
};

struct LITTAB
{
	int index ;
	char literal[10] ;
};

int check_string( char string[50] ) ;

int main( void )
{
	struct TERM t[13] ;
	struct UST u[50] ;
	struct IDTAB id[10] ;
	struct LITTAB l[10] ;

	FILE *fin = NULL ;
	char word[10] = {'\0'} ;
	char string[10] = {'\0'} ;
	int i = 0 ;
	int j = 0 ;
	int k = 0 ;
	int a = 0 ;
	int m = 0 ;	// count for UST table
	int n = 0 ;	// count for identifier table
	int z = 0 ;	// count for literal table
	int count = 1 ;
	int flag = 0 ;
	int flag2 = 0 ;

	char ch = '\0' ;

	t[0].index = 1 ;
	strcpy( t[0].symbol , "int" ) ;
	strcpy( t[0].class , "kwd" ) ;

	t[1].index = 2 ;
	strcpy( t[1].symbol , "void" ) ;
	strcpy( t[1].class , "kwd" ) ;

	t[2].index = 3 ;
	strcpy( t[2].symbol , "float" ) ;
	strcpy( t[2].class , "kwd" ) ;

	t[3].index = 4 ;
	strcpy( t[3].symbol , "return" ) ;
	strcpy( t[3].class , "kwd" ) ;

	t[4].index = 5 ;
	strcpy( t[4].symbol , "(" ) ;
	strcpy( t[4].class , "opr" ) ;

	t[5].index = 6 ;
	strcpy( t[5].symbol , ")" ) ;
	strcpy( t[5].class , "opr" ) ;

	t[6].index = 7 ;
	strcpy( t[6].symbol , "{" ) ;
	strcpy( t[6].class , "spr" ) ;

	t[7].index = 8 ;
	strcpy( t[7].symbol , "=" ) ;
	strcpy( t[7].class , "opr" ) ;

	t[8].index = 9 ;
	strcpy( t[8].symbol , "}" ) ;
	strcpy( t[8].class , "spr" ) ;

	t[9].index = 10 ;
	strcpy( t[9].symbol , ";" ) ;
	strcpy( t[9].class , "spr" ) ;

	t[10].index = 11 ;
	strcpy( t[10].symbol , "," ) ;
	strcpy( t[10].class , "opr" ) ;

	t[11].index = 12 ;
	strcpy( t[11].symbol , "\"" ) ;
	strcpy( t[11].class , "spr" ) ;

	fin = fopen( "input.txt" , "r" ) ;

	if( fin == NULL )
	{
		printf( " \n\n\t File opening error ... " ) ;
	}
	else
	{
		while( !feof( fin ) )
		{
			ch = fgetc( fin ) ;

			if( ch != 10 && ch != 32 )
			{
					
/*if( ch == '"')
					{
							word[a] = ch ;
							a++;

						ch = fgetc( fin );
						while(ch!='"')
						{
							word[a] = ch ;
							a++;
						}

							u[k].index = k+1 ;
							u[k].lineno = count ;
							strcpy( u[k].lexeme , word ) ;
							//strcpy( u[k].class , t[j].class ) ;
							u[k].no = 0;
					
					
					}*/
				string[i] = ch ;
				i++ ;


				
			}
				
			
			

			if( ch == 10 || ch == 32 )
			{
				if(string[0]=='"')
				{
						u[k].index = k+1 ;
						u[k].lineno = count ;
						strcpy( u[k].lexeme , string ) ;
						strcpy( u[k].class , "\tstr" ) ;
						u[k].no = 0;
						flag=1;
						k++;
	
				}
				// printf( "\n%s" , string ) ;

				// UST table generation
				
				else
				{
					for( j = 0 ; j < 11 ; j++ )
					{
						if( ! strcmp( string , t[j].symbol ) )
						{
							u[k].index = k+1 ;
							u[k].lineno = count ;
							strcpy( u[k].lexeme , string ) ;
							strcpy( u[k].class , t[j].class ) ;
							u[k].no = t[j].index ;

							k++ ;

							flag = 1 ;

							j = 11 ;
						}
					}
				}
				if( flag != 1 )
				{
					if( ! check_string( string ) )
					{
						// identifier table generation

						for( j = 0 ; j < m ; j++ )
						{
							if( ! strcmp( id[j].identifier , string ) )
							{
								flag2 = 1 ;

								j = m ;
							}
							else
							{
								flag2 = 0 ;
							}
						}

						if( flag2 != 1 )
						{
							id[m].index = m+1 ;
							strcpy( id[m].identifier , string ) ;

							m++ ;
						}

						u[k].index = k+1 ;
						u[k].lineno = count ;
						strcpy( u[k].lexeme , string ) ;
						strcpy( u[k].class , "idf" ) ;
						u[k].no = id[m-1].index ;

						k++ ;
					}
					else
					{
						// literal table generation

						l[n].index = n+1 ;
						strcpy( l[n].literal , string ) ;

						n++ ;

						u[k].index = k+1 ;
						u[k].lineno = count ;
						strcpy( u[k].lexeme , string ) ;
						strcpy( u[k].class , "lit" ) ;
						u[k].no =l[n-1].index ;

						k++ ;
					}
				}

				while( i >= 0 )
				{
					string[i] = '\0' ;
					i-- ;
				}

				i++ ;

				flag = 0 ;
			}

			if( ch == 10 )
			{
				count++ ;
			}
		}

		fclose( fin ) ;
	}

	printf( " \n\n\t UST table : " ) ;

	printf( " \n\n\t Index \t Lineno \t Lexeme \t Class \t No " ) ;

	for( z = 0 ; z < k ; z++ )
	{
		printf( " \n\n\t %d" , u[z].index ) ;
		printf( " \t\t %d" , u[z].lineno ) ;
		printf( " \t\t %s" , u[z].lexeme ) ;
		printf( " \t\t %s" , u[z].class ) ;
		printf( " \t %d" , u[z].no ) ;
	}

	printf( " \n\n\n\n\t Identifier table : " ) ;

	printf( " \n\n\t Index \t Identifier " ) ;

	for( z = 0 ; z < m ; z++ )
	{
		printf( " \n\n\t %d" , id[z].index ) ;
		printf( " \t %s" , id[z].identifier ) ;
	}

	printf( " \n\n\n\n\t Literal table generation : " ) ;

	printf( " \n\n\t Index \t Literal " ) ;

	for( z = 0 ; z < n ; z++ )
	{
		printf( " \n\n\t %d" , l[z].index ) ;
		printf( " \t %s" , l[z].literal ) ;
	}

	return 0 ;
}

int check_string( char string[50] )
{
	int flag = 0 ;
	int i = 0 ;

	for( i = 0 ; i < strlen(string) ; i++ )
	{
		if( isdigit( string[i] ) != 0 )
		{
			flag = 1 ;
		}
		else
		{
			flag = 0 ;
		}
	}

	return flag ;
}
