#include "./client.h"

int main(int argc, char *argv[])
{
    const std::string login_host = (argc > 1) ? argv[1] :  "127.0.0.1";
    const int login_port = (argc > 2) ? std::atoi(argv[2]) : 10000;
    
    Client client(login_host, login_port);
    client.create_socket(0);
    client.create_connection(0);
    if(client.log_in()) client.chat();
    else exit(1);
    std::cout << "Program terminated successfully\n";
}