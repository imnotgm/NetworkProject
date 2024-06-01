#include "./session.h"

// std::map<int, User> members;
// std::map<std::string, int> id_to_sock;
// std::string resoponse_form = "status: %s\r\n"
//                              "content-length: %d\r\n"
//                              "\r\n"
//                              "%s";

bool Session::leave(const std::string &id)
{
    if(members.find(id) == members.end())
        return false;

    members.erase(id);
    return true;
}