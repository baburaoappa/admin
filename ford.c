#include<stdio.h>
int bellman_ford(int graph[20][20],int nv, int e, int edge[20][2]);
int main(void)
{
	int v=0;
	int edge[20][2]={{0}};
	int graph[20][20]={{0}};
	int i=0;
	int j=0;
	int k=0;
	printf("\nEnter number of vertices:");
	scanf("%d",&v);
	printf("\nEnter adjacency matrix:");
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
		{
			printf("\nEnter weight of edge [%d][%d]",i,j);
			scanf("%d",&graph[i][j]);
			if(graph[i][j]!=0)
			{
				edge[k][0]=i;
				edge[k][1]=j;
				k++;
			}
		}
	}
	if(bellman_ford(graph,v,k,edge)==1)
	{
		printf("\nNo negative weight cycle.");
	}
	else
	{
		printf("\nNegative weight cycle present.");
	}
	return 0;
}

int bellman_ford(int graph[20][20],int nv, int e, int edge[20][2])
{
	int distance[20]={0};
	int s=0;
	int flag=1;
	int i=0;
	int k=0;
	int u=0;
	int v=0;
    for(i=0;i<nv;i++)
    {
        distance[i]=1000;
    }
        printf("Enter source vertex: ");
        scanf("%d",&s);
        distance[s]=0 ;
    for(i=0;i<nv-1;i++)
    {
        for(k=0;k<e;k++)
        {
            u = edge[k][0] , v = edge[k][1] ;
            if(distance[u]+graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
                for(i=0;i<nv;i++)
            {
            	printf("\t%d",distance[i]);
            }
            printf("\n");
            }
            

        }
    }
    for(k=0;k<e;k++)
    {
        u = edge[k][0] , v = edge[k][1] ;
        if(distance[u]+graph[u][v] < distance[v])
        {
            flag = 0 ;
        }
    }
    
        return flag;

}