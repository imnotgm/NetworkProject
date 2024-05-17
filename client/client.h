#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <cerrno>
#include <string>
#include <vector>
#include <set>

namespace command
{
    enum Commands
    {
        NOT_CMD,
        INVALID,
        QUIT,
        HELP,
        JOIN,
        LEAVE,
        USER_LIST,
        CHATROOM_LIST,
    };
}

command::Commands get_command(std::string cmd);

class Client
{
private:
    char *id;   // max length 256
    int sock_fd;
    struct sockaddr_in server;

public:
    Client();
    ~Client();

    int Socket();
    int Connect(int sock_fd, const char *(&host), int port);
    bool log_in(const std::string id);
};
