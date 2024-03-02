#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <vector>
#include <algorithm>

const int MAX_CLIENTS = 10;
const int BUF_SIZE = 64;

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        std::cerr << "Failed to set socket options\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = 0;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        std::cerr << "Failed to bind socket\n";
        return 1;
    }

    socklen_t len = sizeof(server_addr);
    getsockname(sockfd, (struct sockaddr *)&server_addr, &len);
    std::cout << "Server started on port: " << ntohs(server_addr.sin_port) << '\n';

    if (listen(sockfd, MAX_CLIENTS) == -1) {
        std::cerr << "Failed to listen input message\n";
        return 1;
    }

    std::vector<int> client_sockets;

    while (true) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int max_sd = sockfd;

        for (const auto& socket : client_sockets) {
            FD_SET(socket, &readfds);
            max_sd = std::max(max_sd, socket);
        }

        int activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);

        if (activity < 0) {
            std::cerr << "Select error\n";
            return 1;
        }

        if (FD_ISSET(sockfd, &readfds)) {
            int new_socket = accept(sockfd, nullptr, nullptr);
            if (new_socket < 0) {
                std::cerr << "Failed accepting client request\n";
                continue;
            }

            std::cout << "New connection, socket fd is " << new_socket << std::endl;
            client_sockets.push_back(new_socket);
        }

        for (auto it = client_sockets.begin(); it != client_sockets.end(); ++it) {
            int client_socket = *it;
            if (FD_ISSET(client_socket, &readfds)) {
                char buffer[BUF_SIZE];
                int num_bytes_recv = recv(client_socket, buffer, BUF_SIZE - 1, 0);

                if (num_bytes_recv <= 0) {
                    std::cout << "Client disconnected, socket fd is " << client_socket << std::endl;
                    close(client_socket);
                    it = client_sockets.erase(it);
                } else {
                    buffer[num_bytes_recv] = '\0';
                    std::cout << "Received from client " << client_socket << ": " << buffer << std::endl;
                }
            }
        }

    }
    close(sockfd);
}
