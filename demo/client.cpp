#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {

    // 1. Create an IPv4 UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    // 2. Describe the server
    struct sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;

    // Server is listening on port 5000
    server_addr.sin_port = htons(5000);

    // Server IP
    inet_aton("127.0.0.1", &server_addr.sin_addr);

    const char* message = "Hello from UDP client!";

    // 3. Send message to server
    sendto(
        sockfd,
        message,
        strlen(message),
        0,
        (struct sockaddr*)&server_addr,
        sizeof(server_addr)
    );

    // 4. Receive reply from server
    char buffer[1024];

    struct sockaddr_in from_addr{};
    socklen_t from_len = sizeof(from_addr);

    int bytes_received = recvfrom(
        sockfd,
        buffer,
        sizeof(buffer) - 1,
        0,
        (struct sockaddr*)&from_addr,
        &from_len
    );

    if (bytes_received == -1) {
        perror("recvfrom");
        close(sockfd);
        return 1;
    }

    buffer[bytes_received] = '\0';

    cout << "Server says: " << buffer << "\n";

    // 5. Close socket
    close(sockfd);

    return 0;
}
