#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <pthread.h>
#include <ctype.h> 
#include <limits.h>
#define PORT 8080

pthread_t tid[100];

void register_akun(char buffer[], int sock, int valread){
    char username[100] = {0};
    char password[100] = {0};
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
		send(sock, username, strlen(username), 0);
    send(sock, password, strlen(password), 0);
    
    valread = read(sock , buffer, 1024);
    printf("%s\n", buffer);
}

void login_akun(char buffer[], int sock, int valread){
    char username[200] = {0};
    char password[100] = {0};
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);
		send(sock, username, strlen(username), 0);
    send(sock, password, strlen(password), 0);

    valread = read(sock , buffer, 1024);
    printf("%s\n", buffer);
}

int main() {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_address;
    int command;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_address, '0', sizeof(serv_address));

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }


    while(1) 
    {
        if (connect(sock, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0) 
        {
            printf("\nConnection Failed \n");
            return -1;
        }
        char buffer[1024] = {0}, buffer2[1024] = {0};
        printf("1. Login\n2. Register\nChoices: ");
        scanf("%s", buffer);
        send(sock, buffer, strlen(buffer), 0 );
        if (strcmp(buffer,"login") == 0)
        {
           login_akun(buffer2, sock, valread);
        }else if(strcmp(buffer,"register") == 0){
           register_akun(buffer2, sock, valread);
        }
    }
    return 0;
}
