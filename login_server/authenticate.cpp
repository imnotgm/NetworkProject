#include "./login_server.h"

bool authenticate(std::string id)
{
    auto iter = user_list.find(id);
    if(iter == user_list.end())
        return true;
    return false;
}