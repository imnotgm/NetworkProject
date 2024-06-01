#include "./login_server.h"

int msg_handler(int sock, std::string request, std::string status_code, std::string body)
{
    std::string response_msg =
                "status-code: %s\r\n"
                "content-length: %d\r\n"
                "\r\n"
                "%s";
    std::string id = users[sock].id;

    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    snprintf(buf, BUFSIZ, response_msg.c_str(), status_code.c_str(), body.length(), body.c_str());

    if(send(sock, buf, strlen(buf), 0) < 0)
    {
        printf("[msg_handler] error: Failed to send response to user %s's request(%s).\n", id.c_str(), request.c_str());
        return -1;
    }
    printf("[msg_handler] Succeeded to send response to user %s's request(%s).\n", id.c_str(), request.c_str());
    return 0;
}