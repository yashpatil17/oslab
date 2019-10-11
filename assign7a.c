#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main()
{
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	char input[100];
	char final[100];
	char buffer[100];
	char filename[10];
	pid_t pid;
	FILE *fptr; 
	if(pipe(fd1)==-1)
	{
		printf("\n Sorry...Pipe failed..!!");
	}

	if(pipe(fd2)==-1)
	{
		printf("\n Sorry...Pipe failed..!!");
	}

	pid=fork();
	
	if(pid<0)
	{
		printf("\n Failed");
	}
	if(pid>0)
	{
	        printf("\nEnter the pathname::");
	        scanf("%s",filename);
	       
		printf("\n Welcome to Parent process.\n");
		close(fd1[0]);
		write(fd1[1],filename,strlen(filename)+1);
		close(fd1[1]);
		close(fd2[1]);
		read(fd2[0],buffer,100);
		close(fd2[0]);
		printf("\nParents recieves file\n");
		printf("\n Final concatenate string is\n");
		fptr=fopen(filename,"r");
		fgets(final,100,fptr);
		printf("%s\n",final );   
    }
    else
    {
    	printf("\n Welcome to child process.");
    	close(fd1[1]);
        read(fd1[0],filename,20);
        close(fd1[0]);
		//printf("\nChild:File Recieved\n");
        fptr=fopen(filename,"a+");
	    printf("\nEnter a text ::");
	    scanf("%s",&input);
        fputs(input,fptr);
       
        //printf("\nChild:Contents Successfully Written To File %s\n",buffer);
        printf("\nChild is Transferring File To Parent Process\n");
        close(fd2[0]);
        write(fd2[1],buffer,20);
        close(fd2[1]);
	}
}

