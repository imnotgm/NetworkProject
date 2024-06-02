#include "./client.h"

Client::Client() {}

Client::~Client()
{
    for(int i = 0; i < 2; i++)
        close(client_socks[i]);
}