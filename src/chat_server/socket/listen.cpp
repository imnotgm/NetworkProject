#include "../chat_server.h"

void server_listen(int sock, int backlog)
{
    if(listen(sock, backlog) < 0)
        printf("[server_listen] error: Failed to listen");
}