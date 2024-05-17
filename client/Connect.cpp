#include "client.h"

// connect to a server
int Client::Connect(const char *(&host), int port)
{
    this->server.sin_family = AF_INET;
    this->server.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server.sin_addr);

    if(connect(this->sock_fd, (struct sockaddr *) &this->server, sizeof(this->server)) == -1)
    {
        printf("Failed to connect to the server.\n");
        close(this->sock_fd);
        continue;
    }
}