#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int BUF_SIZE = 64;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <server_port> <i>\n";
        return 1;
    }
    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    int i = atoi(argv[3]);

    // Create a socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    memset(&(server_addr.sin_zero), '\0', 8);

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        std::cerr << "Failed to connect\n";
        return 1;
    }

    // Send data to server
    char buf[BUF_SIZE];
    snprintf(buf, BUF_SIZE, "%d", i);
    while(1) {
        if (send(sockfd, buf, strlen(buf), 0) == -1) {
            std::cerr << "Failed to send message\n";
            close(sockfd);
            return 1;
        }
        std::cout << "Message " << i << " sent to server\n";
        sleep(i);
    }
    close(sockfd);
    return 0;
}