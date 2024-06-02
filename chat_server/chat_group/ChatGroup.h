#ifndef CHAT_GROUP_H
#define CHAT_GROUP_H

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
#include <format>
#include <map>
#include <vector>
#include "../../login_server/user/user.h"

class ChatGroup
{
private:
    char buf[BUFSIZ];
    std::string name;
    std::map<std::string, User> members;

public:
    ChatGroup() {};
    ChatGroup(std::string name, std::string id, User user);
    ~ChatGroup();

    bool empty();
    bool isMember(const std::string &id);
    bool join(const std::string &id, User &user);
    bool leave(const std::string &id);
    void broadcast(std::string msg_type, std::string id, std::string body);
};

#endif