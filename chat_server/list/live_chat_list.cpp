#include "../chat_server.h"

std::string live_session_list()
{
    std::string list = "[live sessions]\n";
    int cnt = 0;
    for(auto &session : sessions)
    {
        auto &name = session.first;
        list += "- " + name + "\n";
        cnt++;
    }
    if(cnt == 0)
        return "No available sessions\n";

    return list;
}