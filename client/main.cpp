#include "./client.h"

int main(int argc, char *argv[])
{
    const std::string host = (argc > 1) ? argv[1] :  "127.0.0.1";
    const int port = (argc > 2) ? std::atoi(argv[2]) : 8000;
    
    Client client(host, port);
    client.create_socket();
    client.create_connection();
    for(int i = 1; i <= 5; i++)
    {
        if(client.log_in()) break;
        char ans;
        std::cout << "Log-in attempt(" << i << "/5), continue? [Y/N]: " << i;
        std::cin >> ans;

        if(ans == 'y' || ans == 'Y') continue;
        break;
    }
    client.chat();

    std::cout << "Program terminated\n";
}