#include "../login_server.h"

int server_socket()
{
    int sock;
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation failed.\n");
        close(sock);
    }
    return sock;
}