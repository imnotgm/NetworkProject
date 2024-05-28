#include "../login_server.h"

void server_bind(int sock, int port)
{
    struct sockaddr_in server;

    int opt = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        printf("Failed to set socket option");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(sock, (sockaddr *)&server, sizeof(server)) < 0)
        printf("Failed to bind.\n");
}