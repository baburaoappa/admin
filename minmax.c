#include<stdio.h>
void minmaxfunc(int arr[10],int i,int j,int *min,int *max);

int main(void)
{
	int num=0;
	int i=0;
	int min=0;
	int max=0;
	//int min1=0;
	int arr[10]={0};

	printf("\nEnter the number of elements:");
	scanf("%d",&num);

	while(num<=0)
	{
		printf("\nRe enter the number of elements:");
		scanf("%d",&num);
	}
	for(i=0;i<num;i++)
	{
		printf("\nEnter %d element:",i+1);
		scanf("%d",&arr[i]);
	}
	printf("\n");
	printf("\nElements are:");
	printf("\n");
	for(i=0;i<num;i++)
	{
		printf("%d",arr[i]);
	}
	minmaxfunc(arr,0,num-1,&min,&max);
	printf("\nThe minimum number is:%d",min);
	printf("\nThe maximum number is:%d",max);


}
void minmaxfunc(int arr[10],int i,int j,int *min,int *max)
{
	int min1=0;
	int max1=0;
	int mid=0;

	if(i==j)
	{
		*min=arr[i];
		*max=arr[i];
	}
	else if(i==j-1)
	{
		if(arr[i]<arr[j])
		{
			*min=arr[i];
			*max=arr[j];

		}
		else
		{
			*min=arr[j];
			*max=arr[i];

		}
	}
	else
	{
		mid=(i+j)/2;
		minmaxfunc(arr,i,mid,min,max);
		printf("\ni = %d",i);
		printf("\nj= %d",mid);
		printf("\nMin = %d",*min);
		printf("\nMax = %d",*max);
		printf("\n");

		minmaxfunc(arr,mid+1,j,&min1,&max1);
		printf("\ni = %d",mid+1);
		printf("\nj= %d",j);
		printf("\nMin = %d",min1);
		printf("\nMax = %d",max1);
		printf("\n");

		if (min1 < *min)
		{

			*min = min1;

		}
		if (max1 > *max)
		{
			*max = max1;

		}

	}

}