#include "./login_server.h"

int server_socket()
{
    int sock_fd;
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation failed.\n");
        close(sock_fd);
    }
    return sock_fd;
}