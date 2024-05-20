#include "./login_server.h"

int connection_handler(int sock_fd, const std::string& file_path)
{
    char buf[BUFSIZ];
    int new_socket;
    int max_sd = sock_fd;

    fd_set read_sds;
    std::map<int, User> clients;

    while(1)
    // for(int i = 0; i < 5; i++)
    {
        printf("[Handler] checking while loop\n");
        FD_ZERO(&read_sds);
        FD_SET(sock_fd, &read_sds);

        for(auto &client : clients)
        {
            FD_SET(client.first, &read_sds);
        }

        if((select(max_sd + 1, &read_sds, NULL, NULL, NULL)) < 0)
        {
            printf("[Handler/select] No events on descriptors.\n");
            continue;
        }

        if(FD_ISSET(sock_fd, &read_sds))
        {
            if((new_socket = server_accept(sock_fd)) < 0)
            {
                printf("[Handler/accept] Failed to accept.\n");
                continue;
            }

            FD_SET(new_socket, &read_sds);
            if(new_socket > max_sd)
                max_sd = new_socket;

            User user = tmp_user.back();
            clients[new_socket] = user;
            printf("[Handler] Connection from socket #%d: (ip: %s, port: %d)\n",
                    new_socket, inet_ntoa(user.addr.sin_addr), ntohs(user.addr.sin_port));
            continue;
        }

        std::vector<int> closed_socks;

        for(auto &client : clients)
        {
            printf("[Handler] checking for loop\n");
            int sock = client.first;

            if(!FD_ISSET(sock, &read_sds)) continue;

            int bytes_recv = recv(sock, buf, BUFSIZ, 0);
            printf("[Handler] msg from sock #%d: %dB received\n", sock, bytes_recv);

            //클라이언트가 프로그램을 강제로 종료하여 클라이언트의 소켓은 닫혔는데 서버의 소켓은 열려있다면 recv가 무한하게 0 바이트를 받는다.
            bool conn_lost = bytes_recv <= 0 ? true : false;
            if(conn_lost)
            {
                printf("[Handler] Connection lost.\n");
                closed_socks.push_back(sock);

                continue;
            }

            std::map<std::string, std::string> headers = parseHeaders(buf);
            std::string method = headers["method"];
            std::string status = headers["status"];
            std::string id = headers["id"];
            int fin = std::stoi(headers["fin"]);

            if(fin == 1)
            {
                printf("[Handler] Connection closed.\n");
                closed_socks.push_back(sock);

                continue;
            }
            if(method == "login")
            {
                if(authenticate(id))
                {
                    snprintf(buf, BUFSIZ, response_form.c_str(), "login", "success");
                    if(send(sock, buf, strlen(buf), 0) < 0)
                    {
                        printf("[Handler] Failed to send log-in msg.\n");
                    }
                    printf("[Handler] USER %s log-in.\n", id.c_str());

                    clients[sock].id = id;
                    add_user(id, file_path);

                    continue;
                }

                snprintf(buf, BUFSIZ, response_form.c_str(), "login", "fail");
                if(send(sock, buf, strlen(buf), 0) < 0)
                {
                    printf("[Handler] Failed to send log-in msg.\n");
                }
                printf("[Handler] log-in failed: ID already in use.\n");
            }
            else if(method == "logout")
            {
                snprintf(buf, BUFSIZ, response_form.c_str(), "logout", "success");
                if(send(sock, buf, strlen(buf), 0) < 0)
                {
                    printf("[Handler] Failed to send log-out msg.\n");
                }
                printf("[Handler] USER %s: log-out.\n", id.c_str());
                closed_socks.push_back(sock);

                continue;
            }
            else if(method == "get")
            {
                snprintf(buf, BUFSIZ, response_form.c_str(), "get", "success");
            }
        }
        for(int sock : closed_socks)
        {
            std::string id = clients[sock].id;
            printf("[Handler] closing session for USER %s\n", id.c_str());

            remove_user(id, file_path);
            FD_CLR(sock, &read_sds);
            close(sock);
            clients.erase(sock);
        }
    }
    return 0;
}