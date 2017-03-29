#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
int fd[2];	//variable array having two values is created
pid_t cpid; //process id is created by variable cpid
char a;
char *buffer_write = NULL;	//buffer to write from pipe
char *buffer_read = NULL;	//buffer to read from pipe
FILE *p,*q;	//file descriptors
pipe(fd);	//pipe is created using array fd
if(argc<3) //to check if input and dest file are provided
	{
		printf("The number of arguments entered is insufficient\n");
	}	
else
	{	
		if(fopen(argv[1],"r")==NULL)	//checking if the source file exists
			{
				printf("File does not exist\n");
			}
		else
			{

				p = fopen(argv[1], "r");	//opening input file
				fseek (p, 0, SEEK_END);		//seeking till end to find the size of input file
				long length = ftell (p); 
				fseek (p, 0, SEEK_SET);		//setting pointer to start of input file
				q = fopen(argv[2], "w");	//opening source file
				cpid=fork();				//forking to create both parent and child process
				if(cpid==-1)
					{
						perror("fork");		//fork error checking
						exit(1);
					}
				else if(cpid==0)
					{	
						printf("Child Process :%d\n",getpid());
						close(fd[1]);			//closing write end of pipe
						buffer_write = malloc (length);	//dynamically allocating to buffer
						read(fd[0],buffer_write,length);	//reading from pipe
						printf("Reading from pipe is done\n");
						printf("Do you want to copy to the destination file(Y or N) :");
						scanf("%c",&a);			//permission to copy to dest file
						printf("\n");
						if(a=='Y')
							{	
								
								fwrite(buffer_write,sizeof(char),length,q); 	//writing to dest file
								//printf("%s",buffer_write);
								fflush(stdout);
								printf("Copying to file is done\n");
							}
						else
							{
								printf("Copying has been Terminated\n");
							}
							
					}
				else
					{	
						printf("Parent Process :%d\n",getpid());
						close(fd[0]);					//closing read end of pipe
		  				buffer_read = malloc (length);
						fread (buffer_read, 1, length, p);
						write(fd[1],buffer_read,length); //writing to pipe
						//printf("%s",buffer_read);
						fflush(stdout);
						printf("Write to pipe is done\n");
						
					}
				fclose(p);
				fclose(q);
				free(buffer_read);
				free(buffer_write);
		}
	}
exit(1);
return 0;
}
