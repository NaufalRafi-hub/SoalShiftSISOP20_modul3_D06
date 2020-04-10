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
4a.
4b.
4c.
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
