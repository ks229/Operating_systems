#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>
#define SIZE 100
int array[SIZE];
int array_sorted[SIZE];
int array1[SIZE/2];
int array2[SIZE/2];
void *sort(void *params);
void *merge(void *params);
typedef struct
{
	int start;
	int end;
}parameters;
int main(int argc,char **argv)
{	int count=0;
	pthread_t tid[2];
	int i,j;
	for(i=1,j=0;i<argc;i++,j++)
	{
		array[j]= atoi((char *)argv[i]);
	}
	array[i]='\0';
	count=argc-1;
	printf("Thread One\n");
	parameters *data = (parameters *)malloc(sizeof(parameters));
	data -> start = 0;
	data -> end = (count/2);
	pthread_create(&tid[0],NULL,sort,data);
	pthread_join(tid[0],NULL);
	wait(NULL);
	printf("Thread Two\n");
	data = (parameters *)malloc(sizeof(parameters));
	data -> start = (count/2);
	data -> end = count;
	pthread_create(&tid[1],NULL,sort,data);
	pthread_join(tid[1],NULL);
	wait(NULL);
	printf("Thread Three\n");
	data = (parameters *)malloc(sizeof(parameters));
	data -> start = 0;
	data -> end = count;
	pthread_create(&tid[2],NULL,merge,data);
	pthread_join(tid[2],NULL);
	return 0;
}
void *sort(void *params)
{
	parameters *p = (parameters *)params;
	int beg=p -> start;
	int end=p -> end;
	int temp;
	printf("Before sorting :");
	for(int i=beg;i<end;i++)
		{
		if(i==beg)
		{
			printf("[%d]",array[i]);
		}
		else
		{
		printf("-[%d]",array[i]);
		}
	}
	printf("\n");
	for(int i=beg;i<end;i++)
		{
		for(int j=beg;j<end-1;j++)
			{
			if(array[j]>array[j+1])
				{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				}
			}
		}
	printf("After sorting :");
	if(beg==0)
		{
		for(int i=beg;i<end;i++)
			{
			array1[i]=array[i];
			if(i==0)
			{
				printf("[%d]",array1[i]);
			}
			else
			{
			printf("-[%d]",array1[i]);
			}
		}
		}
	else
		{
		for(int i=beg,j=0;i<end;i++,j++)
			{
			array2[j]=array[i];
			if(i==beg)
			{
				printf("[%d]",array2[j]);
			}
			else
			{
			printf("-[%d]",array2[j]);
			}
		}
		}
	printf("\n");
	pthread_exit(0);
}
void *merge(void *params)
{
	parameters *p = (parameters *)params;
	int beg = p -> start;
	int end = p -> end;
	int j=0,k=0,temp;
	for(int i=beg;i<end;i++)
	{
		if(i<end/2)
		{
			array_sorted[i]=array1[j];
			j++;
		}
		else
		{
			array_sorted[i]=array2[k];
			k++;
		}

	}
	for(int i=beg;i<end;i++)
		{
		for(int j=beg;j<end-1;j++)
			{
			if(array_sorted[j]>array_sorted[j+1])
				{
				temp=array_sorted[j];
				array_sorted[j]=array_sorted[j+1];
				array_sorted[j+1]=temp;
				}
			}
		}
	printf("Merged Sorted Array :");
	for(int i=beg;i<end;i++)
		{
			if(i==beg)
			{
				printf("[%d]",array_sorted[i]);
			}
			else
			{
			printf("-[%d]",array_sorted[i]);
		}
	}

	printf("\n");
	pthread_exit(0);
}

