#include "../chat_server.h"

std::string live_chat_list()
{
    std::string list = "[live chats]\n";
    int cnt = 0;
    for(auto &group : chat_groups)
    {
        auto &name = group.first;
        list += "- " + name + "\n";
        cnt++;
    }
    if(cnt == 0)
        return "No available sessions\n";

    return list;
}