#include "../client.h"

int Client::client_socket(int opt)
{
    std::string target = (opt == 0) ? "log-in" : "chat";

    if((client_socks[opt] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("[client_socket] %s server socket creation failed\n", target.c_str());
        close(client_socks[opt]);
        return -1;
    }
    return opt;
}