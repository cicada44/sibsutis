#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFLEN 81

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in servAddr, clientAddr;
    struct hostent* hp;

    if (argc < 4) {
        printf("missing udpclient hostname port message\n");
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Can't recieve socket\n");
        exit(1);
    }

    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;

    hp = gethostbyname(argv[1]);
    printf("hostname: %s\n", hp->h_name);
    bcopy(hp->h_addr_list[0], &servAddr.sin_addr, hp->h_length);

    servAddr.sin_port = htons(atoi(argv[2]));
    bzero((char*)&clientAddr, sizeof(clientAddr));

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientAddr.sin_port = 0;

    if (bind(sock, (const struct sockaddr*)(&clientAddr), sizeof(clientAddr))) {
        perror("Client can't recieve port.");
        exit(1);
    }

    printf("CLIENT: Ready to sending.\n");

    if (sendto(sock,
               argv[3],
               strlen(argv[3]),
               0,
               (const struct sockaddr*)(&servAddr),
               sizeof(servAddr))
        == -1) {
        perror("sendto was failed. \n");
        exit(1);
    }

    char buf[BUFLEN];
    for (size_t i = 0; i != BUFLEN; ++i)
        buf[i] = 0;

    for (int i = 1; i != 11; ++i) {
        itoa(i, buf);
        if (sendto(sock,
                   buf,
                   strlen(buf),
                   0,
                   (const struct sockaddr*)(&servAddr),
                   sizeof(servAddr))
            == -1) {
            perror("sendto was failed. \n");
            exit(1);
        }
        sleep(i);
        unsigned int length = sizeof(servAddr);
        int msgLength = recvfrom(
                sock, buf, BUFLEN, 0, (struct sockaddr*)(&servAddr), &length);
        printf("CLIENT: LEN of message - %d\n", msgLength);
        printf("CLIENT: Message: %s\n\n", buf);
    }

    printf("CLIENT: Sending's 'done\n");
    close(sock);
}