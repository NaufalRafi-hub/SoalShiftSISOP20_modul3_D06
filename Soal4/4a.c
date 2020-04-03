#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int inputa[4][2], inputb[2][5], output[4][5], *shm_ptr, sum = 0;

    	key_t kunci = 1234;
    	//shmget(key_t key, size_t size, int shmflg);
    	int shmid = shmget(kunci, sizeof(int), IPC_CREAT | 0666);
	//error handling
	if (shmid < 0) {
     		printf("*** shmget error (server) ***\n");
     		exit(1);
	}
   	shm_ptr = shmat(shmid, NULL, 0);
	//error handling
	if (*shm_ptr == -1) {
    		printf("*** shmat error (server) ***\n");
     		exit(1);
	}
	//input mariks a
    	for (int i = 0; i < 4; i++){
    		for (int j = 0; j < 2; j++){
    	    		inputa[i][j]=1;
		}
	}
	//input matriks b
	for (int k = 0; k < 2; k++){
    		for (int l = 0; l < 5; l++){
    	    		inputb[k][l]=1;
		}
	}
	//untuk menghitung perkalian matriks
	for (int c = 0; c < 4; c++) {
		for (int d = 0; d < 5; d++) {
        		for (int x = 0; x < 2; x++) {
         			sum = sum + inputa[c][x] * inputb[x][d];
       			 }
 
        	output[c][d] = sum;
        	sum = 0;
		}
    	}
	//untuk menprint hasil perkalian
	for (int w = 0; w < 4; w++) {
        	for (int s = 0; s < 5; s++) {
            		*shm_ptr = output[w][s];
           		sleep(1);
           		printf("%d\n", *shm_ptr);
        	}
    	}

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
