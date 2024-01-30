#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 81

int main()
{
    int sockMain, msgLength;
    unsigned int length;
    struct sockaddr_in servAddr, clientAddr;
    char buf[BUFLEN], sendBuf[BUFLEN], firstMsgBuf[BUFLEN];
    for (size_t i = 0; i != BUFLEN; ++i) {
        buf[i] = 0;
        sendBuf[i] = 0;
        firstMsgBuf[i] = 0;
    }

    if ((sockMain = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Server cannot open socket for UDP.");
        exit(1);
    }

    bzero((char*)&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = 0;

    if (bind(sockMain, (struct sockaddr*)(&servAddr), sizeof(servAddr))) {
        perror("Server binding unsuccess.");
        exit(1);
    }

    length = sizeof(servAddr);
    if (getsockname(sockMain, (struct sockaddr*)(&servAddr), &length)) {
        perror("Call getsockname failed.");
        exit(1);
    }

    printf("SERVER: port number - %d\n", ntohs(servAddr.sin_port));
    while (1) {
        length = sizeof(clientAddr);
        bzero(buf, sizeof(BUFLEN));
        msgLength = recvfrom(
                sockMain,
                buf,
                BUFLEN,
                0,
                (struct sockaddr*)(&clientAddr),
                &length);
        if (msgLength < 0) {
            perror("Bad client socket.");
            exit(1);
        } else if (msgLength <= 3) {
            for (int i = 0; i != BUFLEN; ++i) {
                sendBuf[i] = firstMsgBuf[i];
            }
            strcat(sendBuf, "\n\t\tMessage number: ");
            strcat(sendBuf, buf);
            sendto(sockMain,
                   sendBuf,
                   strlen(sendBuf),
                   0,
                   (const struct sockaddr*)(&clientAddr),
                   sizeof(clientAddr));
        } else {
            for (int i = 0; i != BUFLEN; ++i) {
                firstMsgBuf[i] = buf[i];
            }
        }
        printf("SERVER: IP client address: %d\n",
               inet_ntoa(clientAddr.sin_addr));
        printf("SERVER: PORT client: %d\n", ntohs(clientAddr.sin_port));
        printf("SERVER: LEN of message - %d\n", msgLength);
        printf("SERVER: Message: %s\n\n", buf);
    }
}
