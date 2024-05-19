#include "./login_server.h"

void server_bind(int sock_fd, int port)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if(bind(sock_fd, (sockaddr *)&server, sizeof(server)) < 0)
        printf("Failed to bind.\n");
}