#include "../client.h"

int Client::client_socket(int opt)
{
    std::string dest = (opt == 0) ? "log-in" : "chat";

    if((client_socks[opt] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("error: (client_socket) Failed to create socket for %s server.\n", dest.c_str());
        close(client_socks[opt]);
        return -1;
    }
    return opt;
}