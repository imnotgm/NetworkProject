#include "./client.h"

int Client::chat()
{
    msg_handler(1, "", this->id, "");
    printf( "Usage: -[option] [args]\n"
            "Option:\n"
            "  -help show detailed usage information\n\n");

    char buf[BUFSIZ];
    int client_sock = client_socks[1];
    int max_fd = client_sock + 1;
    fd_set read_fds;

    while(1)
    {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(client_sock, &read_fds);
        memset(buf, 0, BUFSIZ);

        if((select(max_fd, &read_fds, NULL, NULL, NULL)) < 0)
        {
            printf("error: (chat/select) No events on descriptors.\n");
            continue;
        }

        if(FD_ISSET(STDIN_FILENO, &read_fds))
        {
            std::string input;
            std::getline(std::cin, input);

            if(std::cin.fail() || std::cin.eof())
            {
                std::cout << "Connection closed.\n";
                return 0;
            }

            if(input.empty()) continue;

            int opt;
            std::string request, id, session, body;

            if(input.find('-') == 0)
            {
                input.erase(0, 1);
                std::vector<std::string> args = split(input, " ", 2);

                // cmd ls [user/chat]
                if(args[0] == "ls")
                {
                    request = "GET /";
                    request += args[1];
                    msg_handler(opt = 1, request, this->id, this->session, body = args[1]);
                }
                // cmd create [chat] [user1 user2 user3 ...]
                else if(args[0] == "new")
                {
                    msg_handler(opt = 1, request = "CHAT /new", this->id, session = args[1], body = args[2]);
                    this->session = args[1];
                }
                // cmd join [chat]
                else if(args[0] == "join")
                {
                    msg_handler(opt = 1, request = "CHAT /join", this->id, session = args[1]);
                    this->session = args[1];
                    continue;
                }
                // cmd leave
                else if(args[0] == "leave")
                {
                    msg_handler(opt = 1, request = "CHAT /leave", this->id, this->session);
                    this->session = "";
                }
                else
                {
                    printf("ChatPJO: '%s' is not a ChatPJO command. See '-help'.\n", args[0].c_str());
                }
            }
            else if(this->session.empty())
            {
                printf("ChatPJO: You must join a chat first to send a message.\n");
            }
            else
            {
                msg_handler(opt = 1, request = "CHAT /broadcast", this->id, this->session, input);
            }
            continue;
        }
        if(FD_ISSET(client_sock, &read_fds))
        {
            int bytes_recv = recv(client_sock, buf, BUFSIZ, 0);
            bool conn_lost = (bytes_recv <= 0) ? true : false;
            if(conn_lost)
            {
                printf("error: (recv) Connection lost.\n");
                close(client_sock);
                FD_CLR(client_sock, &read_fds);
                max_fd = STDIN_FILENO + 1;

                return -1;
            }

            std::map<std::string, std::string> headers = parseHeaders(buf);
            std::string status_code = headers["status-code"];
            std::string content_type = headers["content-type"];
            // int len = std::stoi(headers["content-length"]);
            std::string body = headers["body"];

            if(status_code == "OK")
            {
                printf("%s\n", body.c_str());
            }
            else if(status_code == "Bad Request")
            {
                printf("%s: %s\n", content_type.c_str(), body.c_str());
            }
            continue;
        }
    }
    return 0;
}