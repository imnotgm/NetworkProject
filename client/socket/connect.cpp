#include "../client.h"

int Client::client_connect(int opt, std::string host, int port)
{
    std::string target = (opt == 0) ? "log-in" : "chat";

    struct sockaddr_in server;
    server.sin_family = AF_INET;
	server.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server.sin_addr);

    if(connect(client_socks[opt], (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("[cleint_connect] Failed to connect to %s server.\n", target.c_str());
        close(client_socks[opt]);
        return -1;
    }
    servers[opt] = server;
    return opt;
}