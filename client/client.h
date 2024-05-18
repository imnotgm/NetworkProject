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
#include "../command/command.h"

class Client
{
private:
    std:: string id;
    int sock_fd;
    std::pair<std::string, int> login_server;
    std::pair<std::string, int> chat_server;
    struct sockaddr_in server;

public:
    Client(std::string host, int port);
    ~Client();
    
    void set_server(std::string host, int port);
    int create_socket();
    void create_connection();
    bool log_in();
    int chat();
};
