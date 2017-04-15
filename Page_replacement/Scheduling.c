#include "pagealgos.h"
int main(int argc,char *argv[])
{	
	int i;
	p=fopen(argv[1],"r");
	printf("ALGO	|	1	|	4	|	6	|	10	|\n");
	i=array_convert(argv[1]);
	fclose(p);
	fifo(i);
	optimal(i);
	lru(i);
	return 0;
}
int array_convert(char argv[])
{
	char *q=malloc(sizeof(int));
	int tmp=0,i=0;
	while((*q=fgetc(p))!=EOF)
	{
		if(*q==',')
		{
			array[i]=tmp;
			tmp=0;
			i++;	
		}
		else
		{
			tmp=tmp*10+atoi(q);
		}
	}
	array[i++]=tmp;
	array[i]='\0';
	return i;
}
int fifo(int no)
{	
	printf("FIF0	|	");
	int k=1;
	while(k<=10)
	{
		if(k==7)
		{
			k=6;
		}
		int i=0,count=0,count1=0;
		int frames[k];
		for(int j=0;j<k;j++)
		{
			frames[j]=-1;
		}
		int m=0;
		while(i<no)
		{
			count=0;
			for(int l=0;l<k;l++)
			{	
				if(frames[l]!=array[i])
				{
					count++;
				}
			}
			if(count==k)
			{
				frames[m%k]=array[i];
				m++;
				count1++;
			}
			i++;
		}
		printf("%d	|	",count1);
		if(k==6)
		{
			k=7;
		}
		k=k+3;
	}
	printf("\n");
	return 0;
}

int optimal(int no)
{
	int k=1;
	printf("OPTIMAL	|	");
	while(k<=10)
	{
		if(k==7)
		{
			k=6;
		}
		int count2=0,j=0,count1,flag=0;
		int count[k],frames[k];
		for(int i=0;i<k;i++)
		{
			frames[i]=-1;
		}
		while(j<no)
		{
			count1=0;
			for(int i=0;i<k;i++)
			{
				if(frames[i]!=array[j])
				{
					count1++;
				}
				count[i]=0;
			}
			if(count1==k)
			{
				for (int i=0;i<k;i++)
				{
					int m=j;
					while((m<no)&&(frames[i]!=array[m]))
					{
						count[i]=count[i]+1;
						m++;
					}
				}
				int max=count[0];
				flag=0;
				for (int i=0;i<k;i++)
				{
					if(max<count[i])
					{
						max=count[i];
						flag=i;
					}
				}
				frames[flag]=array[j];
				count2++;
				j++;
			}
			else
			{
				j++;
			}
		}
		printf("%d	|	",count2);
		if(k==6)
		{
			k=7;
		}
		k=k+3;
	}
	printf("\n");
	return 0;
}

int lru(int no)
{
	int k=1,count;
	printf("LRU	|	");
	while(k<=10)
	{
		if(k==7)
		{
			k=6;
		}
		int i=0,count1[k],frames[k],flag=0,count2=0;
		for(int j=0;j<k;j++)
		{
			frames[j]=-1;
			count1[j]=0;
		}
		while(i<no)
		{
			count=0;
			for(int j=0;j<k;j++)
			{
				if(frames[j]!=array[i])
				{
					count++;
					count1[j]=count1[j]+1;
				}
				else if(frames[j]==array[i])
				{
					count1[j]=0;
					j=k;
				}
			}
			if(count==k)
			{
				int max = count1[0];
				flag = 0;
				for (int j=0;j<k;j++)
				{
					if(max<count1[j])
					{
						max=count1[j];
						flag=j;
					}
				}
				frames[flag]=array[i];
				count2++;
				count1[flag]=0;
				}
			i++;
		}
		printf("%d	|	",count2);
		if(k==6)
		{
			k=7;
		}
		k=k+3;
	}
	printf("\n");
	return 0;
}
