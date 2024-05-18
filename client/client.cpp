#include "./client.h"

Client::Client(std::string host, int port)
{
    login_server.first = host;
    login_server.second = port;
}

void Client::set_server(std::string host, int port)
{
    chat_server.first = host;
    chat_server.second = port;
}

Client::~Client() {close(sock_fd);}