#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#define MAX 50
pthread_mutex_t forks;
pthread_cond_t freed[MAX];
int NoPhil;
int *timed;
char *fork_state;
int display();
int pickup_fork(int phil);
int return_fork(int phil);
void *activity(int phil);
int main()
{	
	clock_t t;
	char choice='Y';
	int err_mutex,err_cond,err_thread;
	printf("Enter the number of philosophers :");
	scanf("%d",&NoPhil);
	t=clock();
	pthread_t philosopher[NoPhil];
	fork_state=malloc(NoPhil*sizeof(char));
	timed=malloc(NoPhil*sizeof(int));
	while(choice=='Y')
	{
		for(int i=0;i<NoPhil;i++)
		{
			err_cond=pthread_cond_init(&freed[i],NULL);
			if(err_cond)
			{
				printf("Condition initialization failed\n");
			}
		}		
		err_mutex=pthread_mutex_init(&forks,NULL);
		if(err_mutex)
		{
			printf("Mutex initialization failed\n");
		}
		for(int i=0;i<NoPhil;i++)
		{	
			fork_state[i]='F';
			err_thread=pthread_create(&philosopher[i],NULL,(void*)activity,(int*)i);
			if(err_thread)
			{
				printf("Thread creation failed\n");
			}
		}
		for(int i=0;i<NoPhil;i++)
		{	
			pthread_join(philosopher[i],NULL);
		}
		printf("Do you want to continue(Y/N):");
		scanf(" %c",&choice);
	}
	t=clock()-t;
	printf("	--Summary--\n");
	display();
	double total_time=((double)(t))/CLOCKS_PER_SEC;
	printf("Total time taken = %f\n",total_time);
	return 0;
}
void *activity(int phil)
{	
	int k;
	printf("Philosopher[%d] -> Thinking\n",phil);
	sleep(2);
	pickup_fork(phil);
	printf("Philosopher[%d] -> Eating\n",phil);
	k=rand()%3+1;
	timed[phil]=timed[phil]+k;
	sleep(k);
	return_fork(phil);
	printf("Philosopher[%d] -> Thinking\n",phil);
}
int pickup_fork(int phil)
{	
	int k,m;
	pthread_mutex_lock(&forks);
	printf("Philosopher[%d] -> Hungry\n",phil);
	while(fork_state[(phil)%NoPhil]!='F')
	{
		k=pthread_cond_wait(&freed[(phil)%NoPhil],&forks);
	}
	fork_state[phil%NoPhil]='U';
	while(fork_state[(phil+1)%NoPhil]!='F')
	{
		m=pthread_cond_wait(&freed[(phil+1)%NoPhil],&forks);
	}
	fork_state[(phil+1)%NoPhil]='U';
	printf("Philosopher[%d] has fork[%d] and fork[%d]\n",phil,(phil)%NoPhil,(phil+1)%NoPhil);
	pthread_mutex_unlock(&forks);
	return 0;
}
int return_fork(int phil)
{
	pthread_mutex_lock(&forks);
	fork_state[phil%NoPhil]='F';
	pthread_cond_signal(&freed[(phil)%NoPhil]);
	fork_state[(phil+1)%NoPhil]='F';
	pthread_cond_signal(&freed[(phil+1)%NoPhil]);
	printf("Philosopher[%d] has put down fork[%d] and fork[%d]\n",phil,(phil)%NoPhil,(phil+1)%NoPhil);
	pthread_mutex_unlock(&forks);
	return 0;
}
int display()
{	
	printf("No of Philosophers = %d\n",NoPhil);
	for(int i=0;i<NoPhil;i++)
	{
		printf("Total time Philosopher[%d] has eaten =%d seconds\n",i,timed[i]);
	}
	return 0;
}
