#include "./client.h"

void Client::create_connection(int opt)
{
    std::string host = opt == 0 ? login_server.first : chat_server.first;
    int port = opt == 0 ? login_server.second : chat_server.second;

    server.sin_family = AF_INET;
	server.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server.sin_addr);

    if(connect(sock_fd[opt], (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("[client]: Failed to connect.\n");
        close(sock_fd[opt]);
    }
}