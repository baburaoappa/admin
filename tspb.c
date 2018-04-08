#include<stdio.h>
//#include<stdio_ext.h>

#define MAX 10
#define INF 999

int reduce(int m[MAX][MAX],int n);
int branch(int m[MAX][MAX],int n,int start,int cost,int i, int j,int path[MAX]);
void copy(int m[MAX][MAX], int m1[MAX][MAX], int n);
int main(void)
{
	int m[MAX][MAX] = {{0}};
	int m1[MAX][MAX] = {{0}};
	int visited[MAX] = {0} ;
	int path[MAX] = {0} ;

	int n = 0;
	int cost = 0,k=0;
	int ret = 0;
	int start = 0, min = 0;
	int i=0,j=0;
	printf("\nEnter the no. of cities : ");
	scanf("%d",&n);

	printf("\nEnter Matrix : \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
				if(i!=j)
				{
					printf("\nEnter path between M[%d][%d]",i,j);
					scanf("%d",&m[i][j]);
				}
				else
				{
					m[i][j]=999;
				}
		}
	}

	cost = reduce(m,n);

	printf("\nEnter the starting point : ");
	scanf("%d",&start);

	visited[start] = 1;
	path[0] = start;

	for(i=1;i<n;i++)
	{

		min = INF;
		for(j=1;j<n;j++)
		{
			if(visited[j] != 1)
			{
				copy(m,m1,n);
				ret = branch(m1,n,start,cost,path[i-1],j,path);
				if(min > ret)
				{
					min = ret;
					path[i] = j;
				}
			}
		}

		cost = min;

		visited[path[i]] = 1;

		int x = path[i-1];
		for(j=0;j<n;j++)
		{
			m[x][j] = INF;
		}

		x = path[i];
		for(j=0;j<n;j++)
		{
			m[j][x] = INF;
		}

		m[x][0] = INF;

	}
	path[n] = start;

	printf("\ncost : %d\n",cost);
	printf("\npath : ");
	for(i=0;i<=n;i++)
	{
		printf(" %d",path[i]);
	}
	printf("\n");
	return 0;
}

int reduce(int m[MAX][MAX],int n)
{
	int i = 0,j=0,min = 0,k=0;
	int cost = 0;
	int flag = 0;

	//Reducing rows
	for(i=0;i<n;i++)
	{
		flag = 0;
		for(j=0;j<n;j++)
		{
			if(m[i][j] == 0)
			{
				flag = 1;
			}
		}

		if(flag == 0)
		{
			//find min
			min = m[i][0];
			for(j=1;j<n;j++)
			{
				if(m[i][j] < min)
				{
					min = m[i][j];
				}
			}

			if(min != INF)
			{
				cost = cost + min;

				//subtract
				for(j=0;j<n;j++)
				{
					if(m[i][j] != INF)
					{
						m[i][j] = m[i][j] - min;
					}

				}
			}

		}
	}

	//Reducing cols
	for(i=0;i<n;i++)
	{
		flag = 0;
		for(j=0;j<n;j++)
		{
			if(m[j][i] == 0)
			{
				flag = 1;
			}
		}

		if(flag == 0)
		{
			//find min
			min = m[0][i];
			for(j=1;j<n;j++)
			{
				if(m[j][i] < min)
				{
					min = m[j][i];
				}
			}

			if(min != INF)
			{
				cost = cost + min;

				//subtract
				for(j=1;j<n;j++)
				{
					if(m[j][i] != INF)
					m[j][i] = m[j][i] - min;
				}
			}
		}
	}

	return cost;
}


void copy(int m[MAX][MAX], int m1[MAX][MAX], int n)
{
	int i = 0 , j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			m1[i][j] = m[i][j];
		}
	}
}

int branch(int m[MAX][MAX],int n,int start,int cost,int i, int j,int path[MAX])
{
	int pathcost = m[i][j];
	int ret = 0;
	int k=0;

	for(k=0;k<n;k++)
	{
		m[i][k] = INF;
	}
	for(k=0;k<n;k++)
	{
		m[k][j] = INF;
	}
	m[j][start] = INF;

	ret = reduce(m,n);
	ret = ret + cost + pathcost;
	return ret;

}