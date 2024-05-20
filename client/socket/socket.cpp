#include "../client.h"

int Client::create_socket(int opt)
{
    if((sock_fd[opt] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("[client]: Socket creation failed\n");
        close(sock_fd[opt]);
    }
    return sock_fd[opt];
}