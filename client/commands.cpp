#include "client.h"
#include "split.cpp"

using namespace command;

Commands get_command(std::string cmd)
{
    if (cmd[0] != '-') return NOT_CMD;
    cmd.erase(0, 1);

    if (cmd == "q") return QUIT;
    if (cmd == "h") return HELP;

    std::vector<std::string> tokens = split(cmd, " ");
    if(tokens.size() > 2) return INVALID;
    
    if (tokens[0] == "join") return JOIN;
    if (tokens[0] == "leave") return LEAVE;
    if (tokens[0] == "ls")
    {
        if(tokens[1] == "user")
            return USER_LIST;
        if(tokens[1] == "chatroom")
            return CHATROOM_LIST;
    }
    return INVALID;
}