#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFLEN 81

void handle_client(int client_sock) {
    char buf[BUFLEN];
    int msgLength;
    while ((msgLength = recv(client_sock, buf, BUFLEN, 0)) > 0) {
        printf("SERVER: Message: %s\n", buf);
        send(client_sock, "Message received", 16, 0);
    }
    close(client_sock);
}

int main() {
    int sock, client_sock;
    struct sockaddr_in servAddr, cliAddr;
    int new_sock;
    socklen_t cliAddrSize = sizeof(cliAddr);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Server socket creation failed");
        exit(1);
    }

    memset((char *)&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = 0;

    if (bind(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("Server bind failed");
        exit(1);
    }

    if (listen(sock, 5) < 0) {
        perror("Server listen failed");
        exit(1);
    }

    while ((new_sock = accept(sock, (struct sockaddr *)&cliAddr, &cliAddrSize)) > 0) {
        printf("New client arrived!\n");
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            close(sock);
            handle_client(new_sock);
            exit(0);
        } else {
            close(new_sock);
        }
    }

    if (new_sock < 0) {
        perror("Accept failed");
        exit(1);
    }

    close(sock);
    return 0;
}