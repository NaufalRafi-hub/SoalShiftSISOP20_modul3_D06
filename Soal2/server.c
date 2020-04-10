#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <ctype.h> 
#include <limits.h>
#define PORT 8080

typedef struct akun{
		char username[100];
		char password[100];
		}akun;

pthread_t tid[100];

void *server(void *arg){
		int valread;
    int new_socket = *(int *)arg;
    char buffer[1024] = {0},buffer2[1024];
    FILE *pFile;
   	pFile = fopen("/home/syamil/prak3/akun.txt", "a+");
    while (1){
       char temp[512];
       akun daftar;
       
       valread = read(new_socket, buffer, 1024);
       if (strcmp(buffer, "register") == 0){
          valread = read(new_socket, daftar.username, 1024);
          valread = read(new_socket, daftar.password, 1024);
          fwrite(&daftar.username, sizeof(akun), 1, pFile);
          fwrite(&daftar.password, sizeof(akun), 1, pFile);
          fclose(pFile);
          send(new_socket, "register success", strlen("register success"), 0);
       }else if(strcmp(buffer, "login") == 0){
					valread = read(new_socket, daftar.username, 1024);
          valread = read(new_socket, daftar.password, 1024);
          pFile = fopen("/home/syamil/prak3/akun.txt", "r");
       		while(fgets(buffer2, 1024, pFile) != NULL){
       			if((strstr(buffer2, daftar.username)) && (strstr(buffer2, daftar.password)) != NULL){
       				printf("Auth success\n");
       				send(new_socket, "login success", strlen("login success"), 0);
       			}else{
       				printf("Auth failed\n");
       				send(new_socket, "login failed", strlen("login failed"), 0);
       			}
       		}
       		fclose(pFile);
       }
		}
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
		int i = 0;
		while(1){
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    	}
    	pthread_create(&(tid[i]), NULL, &server, &new_socket);
    	i++;
    }
}
