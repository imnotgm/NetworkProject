#include "./login_server.h"

bool id_check(std::string id)
{
    auto iter = user_list.find(id);
    if(iter == user_list.end())
    {
        user_tmp.back().id = id;
        user_list[id] = user_tmp.back();
        user_tmp.pop_back();

        return true;
    }
    return false;
}