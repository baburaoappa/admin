#include<stdio.h>
#include<stdlib.h>

int min(int x, int y,int *p)	//finding min out of 2 values
{
	if(x>y)
	{
		*p = 2;
		return y;
	}
	else
	{
		*p = 1;
		return x;
	}
}

int min1(int x, int y,int z,int *p)		//finding min out of 3 values
{
	if(x>y)
	{
		if(y>z)
		{
			*p = 3;
			return z;
		}
		else
		{
			*p = 2;
			return y;
		}
	}
	else
	{
		if(x>z)
		{
			*p = 3;
			return z;
		}
		else
		{
			*p = 1;
			return x;
		}
	}
}


int main(void)
{

	int m[20][20] = {'\0'};
	int s0[3] = {0};
	int s1[6] = {0};
	int s2[3][2] = {0};
	int s21[3][2] ={{3,4},{2,4},{2,3}};
	int visited[4] = {0};
	int p = 0;
	int path[5] = {1,0,0,0,1};
	//Assuming starting point is 1
	visited[0] = 1;

	int S = 0;
	printf("\nEnter matrix : \n");
	int i = 0,j=0;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			scanf("%d",&m[i][j]);
		}
	}

	// g(2,0)
	s0[0] = m[1][0];
	//g(3,0)
	s0[1] = m[2][0];
	//g(4,0)
	s0[2] = m[3][0];

	printf("\nArray S0\n");
	for(i=0;i<3;i++)
	{
		printf("%d\t",s0[i]);
	}
	//g(2,{3})
	s1[0] = m[1][2] + s0[1];
	//g(2,{4})
	s1[1] = m[1][3] + s0[2];
	//g(3,{2})
	s1[2] = m[2][1] + s0[0];
	//g(3,{4})
	s1[3] = m[2][3] + s0[2];
	//g(4,{2})
	s1[4] = m[3][1] + s0[0];
	//g(4,{3})
	s1[5] = m[3][2] + s0[1];

	printf("\n\nArray S1\n");
	for(i=0;i<6;i++)
	{
 		printf("%d\t",s1[i]);
 	}
	//g(2,{3,4})
	s2[0][0] = min(m[1][2] + s1[3], m[1][3] + s1[5],&p);
	s2[0][1] = p ;
	//g(3,{2,4})
	s2[1][0] = min(m[2][1] + s1[1],m[2][3] + s1[4],&p);
	s2[1][1] = p;
	//g(4,{2,3})
	s2[2][0] = min(m[3][1] + s1[0] ,m[3][2] + s1[2],&p);
	s2[2][1] = p;
	for(i=0;i<3;i++)
	{
		printf("\n");
		for(j=0;j<2;j++)
		{
 			printf("%d\t",s2[i][j]);
 		}	
 	}

	//finding path
	S = min1(m[0][1]+s2[0][0],m[0][2]+s2[1][0],m[0][3]+s2[2][0],&p);
	printf("%d",S);
	printf("%d",p);

	path[1] = p+1;
	visited[path[1] -1 ] = 1;

	path[2] = s21[path[1]-2][s2[path[1]-2][1] - 1];
	visited[path[2] -1 ] = 1;

	for(i=0;i<4;i++)
	{
		if(visited[i] == 0)
			path[3] = i+1;
	}

	printf("\nCost : %d",S);

	printf("\nPath : ");
	for(i=0;i<5;i++)
	{
		printf("%d ",path[i]);
	}

	return 0;
	
}