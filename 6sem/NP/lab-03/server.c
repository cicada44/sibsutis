#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFLEN 81

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int client_sock = *((int *)arg);
    char buf[BUFLEN];
    int msgLength;
    while ((msgLength = recv(client_sock, buf, BUFLEN, 0)) > 0) {
        pthread_mutex_lock(&mutex);
        printf("SERVER: Message: %s\n", buf);
        pthread_mutex_unlock(&mutex);
        send(client_sock, "Message received", 16, 0);
    }
    return NULL;
}

int main() {
    int sock;
    struct sockaddr_in cliAddr;
    int new_sock;
    socklen_t cliAddrSize = sizeof(cliAddr);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Server socket creation failed");
        exit(1);
    }

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = 0;
    memset((char *)&servAddr, 0, sizeof(servAddr));

    if (bind(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Server bind failed");
        exit(1);
    }

    socklen_t lenght = sizeof(servAddr);
    getsockname(sock, (struct sockaddr*)&servAddr, &lenght);

    if (listen(sock, 5) < 0) {
        perror("Server listen failed");
        exit(1);
    }

    printf("Server port: %d\n", ntohs(servAddr.sin_port));

    while ((new_sock = accept(sock, (struct sockaddr*)&cliAddr, &cliAddrSize)) != -1) {
        printf("\n\nNew client arrived!\n\n");
        pthread_t thread;
        int sock_arg[] = {new_sock};
        if (pthread_create(&thread, NULL, handle_client, sock_arg) != 0) {
            perror("Thread creation failed");
            close(new_sock);
            exit(1);
        }
    }

    if (new_sock < 0) {
        perror("Accept failed");
        exit(1);
    }

    // close(sock);
}