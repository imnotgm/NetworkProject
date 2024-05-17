#include "./client.h"

int Client::create_socket()
{
    if(sock_fd = socket(AF_INET, SOCK_STREAM, 0) < 0)
    {
        printf("Socket creation failed\n");
        close(sock_fd);
    }
}