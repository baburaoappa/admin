#include<stdio.h>
struct program
{
	int progno;
	int length;
};
int mrt(struct program p[10],int n,int maxl);
void quicksort(struct program p[10],int first,int last);
int main(void)
{
	int i,j=0;
	int n=0;
	int temp;
	int temp1;
	int maxl=0;
	struct program p[10]={0};
	printf("\nEnter number of programs:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\nEnter length of programs %d:",i+1);
		scanf("%d",&p[i].length);
		p[i].progno = i+1;
	}
	printf("\nEnter maximum length of tape:");
	scanf("%d",&maxl);
	printf("\nArray of programs is:\n");
	for(i=0;i<n;i++)
	{
		printf("\nProgram %d\t \t length=%d",p[i].progno,p[i].length);
	}
	printf("\n");
	quicksort(p, 0, n-1) ;

	printf("\nSorted array of programs is:\n");
	for(i=0;i<n;i++)
	{
		printf("\nProgram %d\t \t length=%d",p[i].progno,p[i].length);
	 }
	 mrt(p,n,maxl);
}
void quicksort(struct program p[10],int first,int last)
{
	int pivot=0;
	int i=0;
	int j=0;
	int k=0;
	int temp=0;
	int temp1=0;

	if(first<last)
	{
		pivot=p[first].length;
		i=first;
		j=last;
		while(i<j)
		{
			while(p[i].length<=pivot && i<last)
			{
				i++;
			}
			while(p[j].length>pivot)
			{
				j--;
			}
			if(i<j)
			{
				temp=p[i].length;
				temp1=p[i].progno;
				p[i].length=p[j].length;
				p[i].progno=p[j].progno;
				p[j].length=temp;
				p[j].progno=temp1;
			}
		}
		//swap pivot element
		temp=p[first].length;
		temp1=p[first].progno;
		p[first].length=p[j].length;
		p[first].progno=p[j].progno;
		p[j].length = temp;
		p[j].progno = temp1;

		quicksort(p,first,j-1);
		quicksort(p,j+1,last);

	}

}


int mrt(struct program p[10],int n,int maxl)
{
	int i=0;
	int c=0;
	int j=0;
	int k=0;
	int length=0;
	int flag=0;
	int mrt=0;
	int count=0;
	float final;
	int tape=0;
	int selected[10]={0};
	printf("\nSelected Programs:");
	
		while((tape+p[i].length)<=maxl && i<n)
		{
			tape=tape+p[i].length;
			i++;
			count++;
		}
		printf("%d",count);

	 for(k=0;k<count;k++)
	 {
		printf("\nprogram %d\t%d\n",p[k].progno,p[k].length);
	 }

	 for(i=0;i<count;i++)
	 {
	 	for(j=0;j<=i;j++)
	 	{
	 		mrt=mrt+p[j].length;
	 	}
	 }

	printf("MRT=%.2f",(float)mrt/count);
	
	return 0;
}

