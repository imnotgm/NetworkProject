#include <string>

namespace command
{
    enum commands
    {
        NOT_CMD,
        INVALID,
        QUIT,
        HELP,
        JOIN,
        LEAVE,
        USER_LIST,
        CHATROOM_LIST,
    };
}

command::commands get_cmd_type(std::string cmd);