#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int inputa[4][2], inputb[2][5], output[4][5], *p, sum = 0, out;

    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    p = shmat(shmid, NULL, 0);

    	for (int i = 0; i < 4; i++){
    		for (int j = 0; j < 2; j++){
    	    		inputa[i][j]=1;
		}
	}
	for (int k = 0; k < 2; k++){
    		for (int l = 0; l < 5; l++){
    	    		inputb[k][l]=1;
		}
	}

	for (int c = 0; c < 4; c++) {
		for (int d = 0; d < 5; d++) {
        		for (int x = 0; x < 2; x++) {
         			sum = sum + inputa[c][x] * inputb[x][d];
       			 }
 
        	output[c][d] = sum;
        	sum = 0;
		}
    	}
	for (int w = 0; w < 4; w++) {
        	for (int s = 0; s < 5; s++) {
            		*p = output[w][s];
           		sleep(1);
           		printf("%d\n", *p);
        	}
    	}

    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}

