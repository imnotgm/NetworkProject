#include "./login_server.h"

int msg_handler(int sock_fd, char buf[], int buf_size,
                    int status, std::string body, std::string method, std::string detail)
{
    std::string response_form =
                "status: %s\r\n"
                "content-length: %d\r\n"
                "\r\n"
                "%s";

    User user = users[sock_fd];
    int content_len = body.length();

    if(status)
    {
        snprintf(buf, buf_size, response_form.c_str(), "OK", content_len, body.c_str());

        if(send(sock_fd, buf, strlen(buf), 0) < 0)
        {
            printf("[Handler] Failed to respond to request(%s) from user(%s).\n", method.c_str(), user.id.c_str());

            return 0;
        }
        printf("[Handler] user(%s) %s: SUCCEED. %s\n", user.id.c_str(), method.c_str(), detail.c_str());
    }
    else
    {
        snprintf(buf, buf_size, response_form.c_str(), "Bad", content_len, body.c_str());
        content_len = strlen(buf);

        if(send(sock_fd, buf, strlen(buf), 0) < 0)
        {
            printf("[Handler] Failed to respond to request(%s) from user(%s).\n", method.c_str(), user.id.c_str());

            return 0;
        }
        printf("[Handler] USER(%s) %s: FAIL. %s\n", user.id.c_str(), method.c_str(), detail.c_str());
    }
    return 1;
}