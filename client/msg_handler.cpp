#include "./client.h"

// std::string request_msg =
//             "method: %s\r\n"
//             "id: %s\r\n"
//             "session: %s\r\n"
//             "\r\n"
//             "%s";

int Client::msg_handler(int opt, std::string method, std::string id, std::string session, std::string body)
{
    std::string dest = (opt == 0) ? "log-in" : "chat";

    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    snprintf(buf, BUFSIZ, request_msg.c_str(), method.c_str(), id.c_str(), session.c_str(), body.c_str());
    
    if(send(client_socks[opt], buf, strlen(buf), 0) < 0)
    {
        printf("error: (msg_handler/send) Failed to send request to %s server.\n", dest.c_str());
        return -1;
    }
    return 0;
}