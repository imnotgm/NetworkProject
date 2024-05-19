#include "./login_server.h"

int server_accept(int sock_fd)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    
    if(accept(sock_fd, (struct sockaddr *) &client_addr, &addr_len) < 0)
    {
        printf("Failed to accept.\n");
    }
    return sock_fd;
}