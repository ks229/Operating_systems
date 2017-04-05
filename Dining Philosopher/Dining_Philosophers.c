/*
NAME        :KARTHIK NATH S
ROLL NO     :1410110187
TEAM MEMBER :JASKARAN SINGH SAINI
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#define MAX 50
struct timespec start,finish;
double elapsed;
pthread_mutex_t forks;		//mutex locks 
pthread_cond_t freed[MAX];	//condition variables
int NoPhil;	
int *timed;
char *fork_state;	//state of the forks
int display();
int pickup_fork(int phil);	//funciton to pickup theforks
int return_fork(int phil);	//funciton to return the forks
void *activity(int phil);	//thread function where philosophers run
int main()
{	
	char choice='Y';
	int err_mutex,err_cond,err_thread;	//error variables if error is encountered
	printf("Enter the number of philosophers :");
	scanf("%d",&NoPhil);
	pthread_t philosopher[NoPhil];
	fork_state=malloc(NoPhil*sizeof(char));	//state of each fork
	timed=malloc(NoPhil*sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &start);
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
	clock_gettime(CLOCK_MONOTONIC, &finish);
	printf("	--Summary--\n");
	display();
	return 0;
}
void *activity(int phil)	//each philosopher runs as a single thread
{	
	int k;
	printf("Philosopher[%d] -> Thinking\n",phil);
	sleep(2);	//philosopher thinks for 2 seconds
	pickup_fork(phil);
	printf("Philosopher[%d] -> Eating\n",phil);
	k=rand()%3+1;	//philosopher eats randomly between 1 to 3 seconds
	timed[phil]=timed[phil]+k;
	sleep(k);
	return_fork(phil);
	printf("Philosopher[%d] -> Thinking\n",phil);
}
int pickup_fork(int phil)
{	
	pthread_mutex_lock(&forks);
	printf("Philosopher[%d] -> Hungry\n",phil);
	while(fork_state[(phil)%NoPhil]!='F')
	{
		pthread_cond_wait(&freed[(phil)%NoPhil],&forks);
	}
	fork_state[phil%NoPhil]='U';
	while(fork_state[(phil+1)%NoPhil]!='F')
	{
		pthread_cond_wait(&freed[(phil+1)%NoPhil],&forks);
	}
	fork_state[(phil+1)%NoPhil]='U';
	printf("Philosopher[%d] has taken fork[%d] and fork[%d]\n",phil,(phil+1)%NoPhil,(phil)%NoPhil);
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
	printf("Philosopher[%d] has put down fork[%d] and fork[%d]\n",phil,(phil+1)%NoPhil,(phil)%NoPhil);
	pthread_mutex_unlock(&forks);
	return 0;
}
int display()
{	
	elapsed=(finish.tv_sec-start.tv_sec);
	elapsed+=(finish.tv_nsec - start.tv_nsec)/1000000000.0;
	printf("No of Philosophers = %d\n",NoPhil);
	for(int i=0;i<NoPhil;i++)
	{
		printf("Total time Philosopher[%d] has eaten =%d seconds\n",i,timed[i]);
	}
	printf("Total time taken = %f secounds\n",elapsed);
	return 0;
}
