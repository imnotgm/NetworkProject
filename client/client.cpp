#include "./client.h"

Client::Client(std::string host, int port)
{
    login_server.first = host;
    login_server.second = port;
}

void Client::set_chat_server(std::string host, int port)
{
    chat_server.first = host;
    chat_server.second = port;
}

Client::~Client()
{
    for(int i = 0; i < 2; i++)
        close(sock_fd[i]);
}