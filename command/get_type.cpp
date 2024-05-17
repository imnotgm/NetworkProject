#include "./command.h"

using namespace command;

commands get_cmd_type(std::string cmd)
{
    if (cmd[0] != '-') return NOT_CMD;
    cmd.erase(0, 1);

    if (cmd == "quit") return QUIT;
    if (cmd == "help") return HELP;
    
    std::vector<std::string> tokens = split(cmd, " ");
    if(tokens.size() > 2) return INVALID;
    
    if (tokens[0] == "list")
    {
        if(tokens[1] == "user")
            return USER_LIST;
        if(tokens[1] == "chatroom")
            return CHATROOM_LIST;
    }
    if (tokens[0] == "join") return JOIN;
    if (tokens[0] == "leave") return LEAVE;
    return INVALID;
}