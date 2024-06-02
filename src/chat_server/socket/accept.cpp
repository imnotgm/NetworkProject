#include "../chat_server.h"

int server_accept(int sock)
{
    int client_sock;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    
    if((client_sock = accept(sock, (struct sockaddr *) &addr, &addr_len)) < 0)
    {
        printf("[server_accept] error: Failed to accept from client.\n");
        close(client_sock);
    }
    
    User user = {"tmp", "", 1, client_sock, addr};
    tmp_user.push_back(user);

    return client_sock;
}