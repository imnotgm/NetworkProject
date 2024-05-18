#include "./client.h"

bool Client::log_in()
{
    char buf[BUFSIZ];
    std::string id;

    bool loggedIn= false;
    int attempt = 1;

    while(attempt <= 5)
    {
        std::cout << "Enter your ID(" << attempt++ << "/5): ";
        std::cin >> id;
        snprintf(buf, BUFSIZ, request_form.c_str(), "login", id);

        if(send(sock_fd[0], buf, strlen(buf), 0) < 0)
        {
            printf("[client/login]: Failed to send to server.\n");
            continue;
        }
        if(recv(sock_fd[0], buf, BUFSIZ, 0) < 0)
        {
            printf("[client/login]: Failed to receive from server.\n");
            continue;
        }

        std::string auth;
        sscanf(buf, "authentication: %s", auth);
        loggedIn = auth == "success" ? true : false;
        if(loggedIn)
        {
            printf("Hello %s.\n", id);
            this->id = id;

            return true;
        }
        else
        {
            printf("ID already taken. Please choose a different ID.\n");
            continue;
        }
    }
    printf("Too many login attempts. Terminating program.");
    return false;
}