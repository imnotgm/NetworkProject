#include "./client.h"

// std::string request_msg =
//             "method: %s\r\n"
//             "id: %s\r\n"
//             "session: %s\r\n"
//             "\r\n"
//             "%s";

bool Client::log_in()
{
    char buf[BUFSIZ];

    // header fields
    std::string method, id, session;

    // flag
    bool authenticated = false;

    for(int attempt = 1; attempt <= 5; attempt++)
    {
        memset(buf, 0, BUFSIZ);

        // set fields and send request msg
        printf("[System] Enter your ID(%d/5): ", attempt);
        std::cin >> id;
        msg_handler(0, method = "LOG IN", id, session = "log-in");

        // recieve and parse response msg from server
        if(recv(client_socks[0], buf, BUFSIZ, 0) < 0)
        {
            printf("[System]: Failed to receive response msg.\n");
            continue;
        }
        std::map<std::string, std::string> headers = parseHeaders(buf);
        std::string status = headers["status"];
        std::string body = headers["body"];
        authenticated = (status == "OK") ? true : false;

        // check authentication
        if(authenticated)
        {
            printf("[System] Hello %s.\n", id.c_str());
            printf("%s\n", body.c_str());
            this->id = id;
            
            return true;
        }

        // if not authenticated
        printf("[System] ID already taken. Please choose a different ID. "
                "Continue to log in? [Y/N]: ");
        char ans[2];
        std::cin >> ans;
        if(strcasecmp(ans, "y"))
            break;
    }

    // notify server of the user's staus
    msg_handler(0, method = "LOG OUT", id = "", session = "log-in");
    printf("[System] Authentication required to proceed further.\n");

    return false;
}