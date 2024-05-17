#include "client.h"

bool Client::log_in()
{
    std::string id;
    std::cout << "Enter your ID: ";
    std::cin >> id;

    if(send(sock_fd, id.c_str(), id.size() , 0) == -1)
    {
        printf("Failed to send ID.");
        close(sock_fd);
        
        return false;
    }

    if(recv(sock_fd, buf, BUFSIZ, 0) < 0)
    {
        printf("Fialed to receive authentication.");

        return false;
    }
    else
    {
        printf("Log-in success.");
        this->id = id;

        return true;
    }
}