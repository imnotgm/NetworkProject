#include "../chat_server.h"

std::string user_list(std::string id)
{
    std::string list = "@" + id + "(you)\n";
    int cnt = 0;
    for(auto &user : users)
    {
        auto &client = user.second;
        if(client.id != id && client.is_available == 1)
        {
            list += "@" + client.id + "\n";
            cnt++;
        }
    }
    if(cnt == 0)
        return "No available users for now.\n";

    return list;
}