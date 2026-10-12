#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(5000);

    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(sockfd);
        return 1;
    }

    cout << "UDP Server listening on port 5000...\n";


    struct sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    char buffer[1024];


    int bytes_received = recvfrom(sockfd,buffer,sizeof(buffer) - 1,0,(struct sockaddr *)&client_addr,&client_len);

    if (bytes_received == -1)
    {
        perror("recvfrom");
        close(sockfd);
        return 1;
    }

    buffer[bytes_received] = '\0';

    cout << "Client says: " << buffer << "\n";

    const char *reply = "Hello from UDP server!";

    sendto(sockfd,reply,strlen(reply),0,(struct sockaddr *)&client_addr,client_len);

    close(sockfd);

    return 0;
}
