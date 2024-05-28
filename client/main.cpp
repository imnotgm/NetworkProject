#include "./client.h"

int main(int argc, char *argv[])
{
    const std::string login_host  = (argc > 1) ? argv[1] :  "127.0.0.1";
    const int login_port = (argc > 2) ? std::atoi(argv[2]) : 10000;
    const std::string chat_host = (argc > 3) ? argv[1] :  "127.0.0.1";
    const int chat_port = (argc > 4) ? std::atoi(argv[2]) : 10001;

    int opt = 0;
    Client client;
    if(client.client_socket(opt) == -1) return -1;
    if(client.client_connect(opt, login_host, login_port) == -1) return -1;

    if(client.log_in())
    {
        opt = 1;
        if(client.client_socket(opt) == -1) return -1;
        if(client.client_connect(opt, chat_host, chat_port) == -1) return -1;
        client.chat();
    }
    std::cout << "Program terminated successfully\n";
}