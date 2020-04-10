# SoalShiftSISOP20_modul3_D06

Soal Shift Modul 1
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)
4. [Soal 4](#4-soal-4)


### 1. Soal 1
### 2. Soal 2
### 3. Soal 3
### 4. Soal 4
#4a.
nomer 4a meminta untuk membuat perkalian matriks, matriks 4x2 dikalikan dengan matrik 2x5, dimana hasil dari program ini akan digunakan nomer 4b, soal mempunyai syarat yaitu harus menggunakan share memory dan isi dari matriks harus di definisikan
```sh
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
```
mendefinisikan key untuk digunakan di fungsi shmget,
shmget berfungsi untuk mengalokasikan segment untuk share memory
mendefinisikan shmid = shmget untuk digunakan di fungsi shmat
shmat berfungsi untuk memanggil agar share memory dimulai, dan ```sh if (*shm_ptr == -1)``` untuk handling error 
```sh
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
```
kodingan template untuk menghitung perkalian matriks
```sh
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
```
pengulangan diatas digunakan untuk menampilkan hasil perkalian dari kedua matriks
```sh *shm_ptr = output[w][s];``` deklarasi ini digunakan untuk fungsi shmdt mengoper hasil dari perkalian yang nanti akan digunakan di nomer 4b

#4b.
4b meminta untuk menampilkan hasil dari program 4a, dan memfaktorialkan hasil tersebut akan tetapi faktorial tersebut mempunyai syarat hasilnya tidak di kali, akan tetapi di jumlah. dan harus menggunakan thread
```sh
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
```
deklarasi sama seperti 4a untuk kebutuhan share memory
kondisi ```sh if (*shm_ptr == -1)``` digunakan untuk error handling
deklarasi thread sebanyak 20 karena jawaban dari 4a sebanyak 20

```sh
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
```
pengulangan sebanyak 20, karena thread yang diinginkan harus sesuai dengan hasil dari 4a (sebanyak 20), 
mendeklarasikan array untuk menyimpan salah satu nilai dari 20.
mendeklarasikan fungsi thread dimana memanggil fungsi playandcount dan mempassing salah satu nilai dari jawaban 4a.
terdapat kondisi ```sh if((j+1) % 5 == 0)``` untuk format print layout matriks
```sh
void playandcount(int n){
    int output=0;

    for(int x = n; x >= 1; x--){
        output += x;
    }

    printf("%d", output);
}
```
fungsi playandcount terdapat pengulangan untuk menghitung faktorial dari nilai yang di passing
```sh output += x;``` untuk menjumlahkan hasil yang sudah difaktorialkan
```sh
for(int k = 0; k < i; k++){
            pthread_join(tid[k],NULL);
        }
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);

}
```
pengulangan untuk menjoinkan smua thread yang ada

#4c.
Maksud soal nomer 4c adalah soal meminta untuk menghitung banyaknya file di directory yang sedang berlangsung, untuk mengecek banyaknya file yang ada yaitu menggunakan ```sh "ls | wc -l"```. 
```sh
int main() 
{ 
	int pipa[2];
	pipe(pipa);
	char *als[] = {"ls", NULL};
	char *awc[] = {"wc", "-l", NULL}; ;
	pid_t p; 
	p = fork();
```
deklarasi pipe, fungsi ls dan wc, dan fork
```sh
//childfork
	if (p == 0){
 
		dup2(pipa[1], 1);
        	close(pipa[0]);
        	close(pipa[1]);

	
        execv("/bin/ls", als);

	} 
  ```
childfork disini sebagai input karena pipe di [1] mempunyai tugas yaitu write, tugas ls disini yaitu membuat list file yang terdapat di directory yang sedang berlangsung
  ```sh
	else //parent fork 
	{ 

		dup2(pipa[0], 0); 
        	close(pipa[0]);
        	close(pipa[1]);
	
	//prints the line count 
	//word count per kata
        execv("/usr/bin/wc", awc);
	exit(0); 
	} 
} 
```
didalam parent fork, terdapat pipe[0] mempunyai tugas yaitu read, tugas wc ini adalah menghitung per kata file yang terdapat di directory yang sedang berlangsung
