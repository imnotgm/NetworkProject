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
    int sock_fd[2];
    std::pair<std::string, int> login_server;
    std::pair<std::string, int> chat_server;
    struct sockaddr_in server;

    std::string request_form =  "method: %s\r\n"
                                "id: %s\r\n"
                                "\r\n";

public:
    Client(std::string host, int port);
    ~Client();
    
    void set_chat_server(std::string host, int port);
    int create_socket(int opt);
    void create_connection(int opt);
    bool log_in();
    int chat();
};
