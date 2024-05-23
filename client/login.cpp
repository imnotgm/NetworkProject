#include "./client.h"

bool Client::log_in()
{
    char buf[BUFSIZ];
    std::string id;

    bool authenticated = false;
    int fin = 0;

    for(int attempt = 1; attempt <= 5; attempt++)
    {
        printf("[System] Enter your ID(%d/5): ", attempt);
        std::cin >> id;

        snprintf(buf, BUFSIZ, request_form.c_str(), "LOG-IN", "online", id.c_str(), fin);

        if(send(sock_fd[0], buf, strlen(buf), 0) < 0)
        {
            printf("[System]: Failed to send request msg.\n");
            continue;
        }
        if(recv(sock_fd[0], buf, BUFSIZ, 0) < 0)
        {
            printf("[System]: Failed to receive response msg.\n");
            continue;
        }

        std::map<std::string, std::string> headers = parseHeaders(buf);
        std::string status = headers["status"];
        std::string body = headers["body"];
        authenticated = (status == "OK") ? true : false;

        if(authenticated)
        {
            printf("[System] Hello %s.\n", id.c_str());
            printf("===========================================\n");
            printf("%s\n", body.c_str());
            printf("===========================================\n");
            this->id = id;
            
            return true;
        }

        printf( "[System] ID already taken. Please choose a different ID. "
                "Continue to log in? [Y/N]: ");
        char ans[10];
        scanf("%s", ans);
        if(strcasecmp(ans, "y"))
            break;
    }
    fin = 1;
    snprintf(buf, BUFSIZ, request_form.c_str(), "LOG-OUT", "offline", id.c_str(), fin);
    send(sock_fd[0], buf, strlen(buf), 0);
    printf("[System] Failed to log-in.\n");

    return false;
}