#include "../login_server.h"

std::string online_users()
{
    // std::string list;
    int cnt = 0;
    std::string online = "";
    for(auto user : users)
    {
        std::string id = user.second.id;
        
        if(user.second.is_available == 1)
        {
            online += "- " + id + "\n";
            cnt++;
        }
    }
    if(cnt == 0)
        return "No Online Users";

    return online;
}