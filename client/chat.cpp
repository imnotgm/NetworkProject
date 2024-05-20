#include "./client.h"

int Client::chat()
{
    std::string msg;
    while(true)
    {
        std::cin >> msg;
        std::cout << msg;
    }
    return 0;
}