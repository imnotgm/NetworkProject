#include "./client.h"

int Client::create_connection()
{
    server.sin_family = AF_INET;
	server.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server.sin_addr);

    if(connect(sock_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connection failed.\n");
        close(sock_fd);
    }
}