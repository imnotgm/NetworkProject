#include "./session.h"

// std::map<int, User> members;
// std::map<std::string, int> id_to_sock;
// std::string resoponse_form = "status: %s\r\n"
//                              "content-length: %d\r\n"
//                              "\r\n"
//                              "%s";

bool Session::join(const std::string &id, User &user)
{
    if(members.find(id) == members.end())
    {
        members[id] = user;
        return true;
    }
    return false;
}