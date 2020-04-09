#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 
	int pipa[2];
	pipe(pipa);
	char *als[] = {"ls", NULL};
	char *awc[] = {"wc", "-l", NULL}; ;
	pid_t p; 
	p = fork();
	
	//childfork
	if (p == 0){
 
		dup2(pipa[1], 1);//output
        	close(pipa[0]);
        	close(pipa[1]);

	
        execv("/bin/ls", als);

	} 
	else //parent fork 
	{ 

		dup2(pipa[0], 0);//input
        	close(pipa[0]);
        	close(pipa[1]);
	
	//prints the line count 
	//word count per kata
        execv("/usr/bin/wc", awc);
	exit(0); 
	} 
} 
