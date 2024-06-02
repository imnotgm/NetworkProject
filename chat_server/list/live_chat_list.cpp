#include "../chat_server.h"

std::string live_chat_list()
{
    std::string list = "";
    int cnt = 0;
    for(auto &group : chat_groups)
    {
        auto &id = group.first;
        list += "@" + id + "\n";
        cnt++;
    }
    if(cnt == 0)
        return  "No available chats. Feel free to open a new chat.\n"
                "usage: -new [name] [members]\n";

    return list;
}