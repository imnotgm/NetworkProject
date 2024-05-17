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
#include "../command/cmd.h"

class Client
{
private:
    char buf[BUFSIZ];
    std:: string id;
    int sock_fd;
    std::string host;
    int port;
    struct sockaddr_in server;

public:
    Client(std::string host, int port);
    ~Client();

    int create_socket();
    int create_connection();
    bool log_in();
    int chat();
};
