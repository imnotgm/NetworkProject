#include "./chat_server.h"

int msg_handler(User &user, std::string status, std::string type, std::string body, std::string method)
{
    std::string response_msg =
                "status: %s\r\n"
                "type: %s\r\n"
                "content-length: %d\r\n"
                "\r\n"
                "%s";

    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    snprintf(buf, BUFSIZ, response_msg.c_str(), status.c_str(), type.c_str(), body.size(), body.c_str());

    if(send(user.sock, buf, strlen(buf), 0) < 0)
    {
        printf("[msg_handler] error: Failed to send response to user %s's request(%s).\n", user.id.c_str(), method.c_str());
        return -1;
    }
    printf("[msg_handler] Succeeded to send response to user(%s)'s request(%s).\n", user.id.c_str(), method.c_str());
    return 0;
}