#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

void playandcount(int n){
    int output=0;

    for(int x = n; x >= 1; x--){
        output += x;
    }

    printf("%d", output);
}
void main(){
        key_t kunci = 1234;
        int *shm_ptr;
        int arr[20];
        int hasil;
        int shmid = shmget(kunci, sizeof(int), IPC_CREAT | 0644);
        shm_ptr = shmat(shmid, NULL, 0);
	//error handling
	if (*shm_ptr == -1) {
     		printf("*** shmat error (server) ***\n");
     		exit(1);
	}
        pthread_t tid[20];
        int i=0;
        for (int j = 0; j < 20; j++){
                arr[j] = *shm_ptr;
                //hasil = arr[j];
                pthread_create(&tid[i], NULL, &playandcount, (void*)arr[j]);
                i++;
                sleep(2);
		//FUNGSI UNTUK PRINT LAYPUT MATRIX
                if((j+1) % 5 == 0){
                        printf("\n");
                } else {
                        printf("\t");
                }
        }
        for(int k = 0; k < i; k++){
            pthread_join(tid[k],NULL);
        }
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);

}
