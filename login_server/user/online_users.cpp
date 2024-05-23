#include "../login_server.h"

std::string online_users()
{
    // std::string list;
    int cnt_o = 0, cnt_x = 0;
    std::string online = "[Online]\n";
    std::string offline = "[Offline]\n";
    for(auto user : users)
    {
        std::string id = user.second.id;
        
        if(user.second.is_available == 1)
        {
            online += "- " + id + "\n";
            cnt_o++;
        }
        else
        {
            offline += "- " + id + "\n";
            cnt_x++;
        }
    }
    if(cnt_o == 0)
        return "\"No Online Users\"";
    if(cnt_x == 0)
        offline += "\"Everyone is online.\"";

    return online + offline;
}