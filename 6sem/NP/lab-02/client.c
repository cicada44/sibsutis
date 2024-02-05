#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <netdb.h>

#define BUFLEN 81

void send_message(int sock, const char *message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Send failed");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int sock, i;
    struct sockaddr_in servAddr;

    if (argc < 2) {
        printf("Usage: %s <server_ip>\n", argv[0]);
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    struct hostent* hp = gethostbyname(argv[1]);
    printf("hostname: %s\n", hp->h_name);
    bcopy(hp->h_addr_list[0], &servAddr.sin_addr, hp->h_length);

    memset((char *)&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("Connect failed");
        exit(1);
    }

    for (i = 1; i <= 10; i++) {
        char buf[BUFLEN];
        for (int i = 0; i != BUFLEN; ++i)
            buf[i] = 0;
        sprintf(buf, "Message %d\0", i);
        send_message(sock, buf);
        sleep(i);
        memset(buf, 0, BUFLEN);
        recv(sock, buf, BUFLEN, 0);
        printf("Received: %s\n", buf);
    }

    close(sock);
}
