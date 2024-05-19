#include "./login_server.h"

int main(int argc, char *argv[])
{
    const int port = (argc > 1) ? std::atoi(argv[1]) : 8000;
    const int backlog = (argc > 2) ? std::atoi(argv[2]) : SOMAXCONN;
    
    int master_socket = server_socket();
    server_bind(master_socket, port);
    server_listen(master_socket, backlog);
}