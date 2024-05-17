#include <string>
#include "../utils/split.cpp"

namespace command
{
    enum commands
    {
        NOT_CMD,
        INVALID,
        QUIT,
        HELP,
        USER_LIST,
        CHATROOM_LIST,
        JOIN,
        LEAVE,
    };
}

command::commands get_cmd_type(std::string cmd);
void man_page();