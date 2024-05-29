#include "../chat_server.h"

std::string user_list()
{
    std::string list = "[online users]\n";
    int cnt = 0;
    for(auto &user : users)
    {
        auto &client = user.second;
        if(client.is_available == 1)
        {
            list += "- " + client.id + "\n";
            cnt++;
        }
    }
    if(cnt == 0)
        return "No available users";

    return list;
}