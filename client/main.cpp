#include "client.h"

int main(int argc, char *argv[])
{
    const std::string host = (argc > 1) ? argv[1] :  "127.0.0.1";
    const int port = (argc > 2) ? std::atoi(argv[2]) : 8000;
    
    Client client(host, port);
    client.create_socket();
    client.create_connection();
    while(client.log_in());
    client.chat();
}