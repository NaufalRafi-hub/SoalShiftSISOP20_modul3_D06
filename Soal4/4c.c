#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 
	int pipe[2];
	pid_t p; 
	p = fork();

	//childfork
	if (p == 0){ 

        dup2(pipe[1], 1);//output
        close(pipe[0]);
        close(pipe[1]);

	char *arg_ls[] = {"ls", NULL};
        execv("/bin/ls", arg_ls);

	} 
	else //parent fork 
	{ 

        	dup2(pipe[0], 0);//input
        	close(pipe[0]);
        	close(pipe[1]);
	
		
	char *arg_wc[] = {"wc", "-l", NULL};
	//prints the line count 
	//word count per kata
        execv("/usr/bin/wc", arg_wc);
	exit(0); 
	} 
} 
