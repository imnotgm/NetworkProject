#include "./client.h"

Client::Client(std::string host, int port) : host(host), port(port) 
{

}

Client::~Client()
{
    close(sock_fd);
}
