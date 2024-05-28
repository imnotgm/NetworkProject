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
#include "../include/utils/utils.h"

class Client
{
private:
    std::string id = "";
    std::string session = "log in";

    int client_socks[2];
    std::map<int, struct sockaddr_in> servers;
    
    std::string request_msg =
                "method: %s\r\n"
                "id: %s\r\n"
                "session: %s\r\n"
                "\r\n"
                "%s";

public:
    Client();
    ~Client();

    int client_socket(int opt);
    int client_connect(int opt, std::string host, int port);

    int msg_handler(int opt, std::string method, std::string id, std::string session, std::string body = "");
    bool log_in();
    int chat();
};
