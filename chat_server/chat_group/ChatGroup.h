#ifndef SESSION_H
#define SESSION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include "../../login_server/user/user.h"

class Session
{
private:
    char buf[BUFSIZ];
    std::string resoponse_msg = "status: %s\r\n"
                                 "type: %s\r\n"
                                 "content-length: %d\r\n"
                                 "\r\n"
                                 "%s";
    std::string name;
    std::map<std::string, User> members;

public:
    Session() {};
    Session(std::string name, std::string id, User user);
    ~Session();

    bool empty();
    bool join(const std::string &id, User &user);
    bool leave(const std::string &id);
    void broadcast(std::string msg_type, std::string id, std::string body);
};

#endif