#include "../login_server.h"

void server_listen(int sock, int backlog)
{
    if(listen(sock, backlog) < 0)
        printf("Failed to listen");
}