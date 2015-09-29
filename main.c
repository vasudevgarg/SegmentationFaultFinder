#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include"modify.c"
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Error!Arguments should be two\n");
		exit(1);
	}
	FILE *fp;
	fp=fopen(argv[1],"r");
	modify(fp);
	int pid=fork();
	if(pid==0)
	{
		execlp("/home/NITJ/Documents/GDB/build.sh","./build.sh",NULL);
	}
	else
	{
		wait(NULL);
	}
	fclose(fp);
	return 0;
}
