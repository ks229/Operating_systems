#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
int main()
{
int i=0,k;
FILE *p;
p = fopen("/home/karthiknath/Desktop/OS/Scheduling_Algo/input.txt", "w");
while(i<100)
{
k = rand()%21;
fprintf(p,"%d",k);
if(i<99)
{
fprintf(p,"%c",',');
}
i++;
}
fclose(p);
return 0;
}
