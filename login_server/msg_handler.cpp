#include "./login_server.h"

int msg_handler(int sock, std::string status, std::string body, std::string method, std::string detail)
{
    std::string response_msg =
                "status: %s\r\n"
                "content-length: %d\r\n"
                "\r\n"
                "%s";

    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);

    User user = users[sock];

    snprintf(buf, BUFSIZ, response_msg.c_str(), status.c_str(), body.length(), body.c_str());

    if(send(sock, buf, strlen(buf), 0) < 0)
    {
        printf("[msg_handler] request(%s) from user user(%s) failed.\n", method.c_str(), user.id.c_str());

        return -1;
    }
    printf("[msg_handler] request(%s) from user(%s) succeeded.\n", method.c_str(), user.id.c_str());

    return 0;
}