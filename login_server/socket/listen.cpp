#include "../login_server.h"

void server_listen(int sock_fd, int backlog)
{
    if(listen(sock_fd, backlog) < 0)
        printf("Failed to listen");
}