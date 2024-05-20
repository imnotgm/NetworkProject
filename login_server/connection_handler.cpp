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

            User new_user = tmp_user.back();
            clients[new_socket] = new_user;
            FD_SET(new_socket, &read_sds);
            if(new_socket > max_sd)
                max_sd = new_socket;

            printf("[Handler] Connection from socket #%d: (ip: %s, port: %d)\n",
                    new_socket, inet_ntoa(new_user.addr.sin_addr), ntohs(new_user.addr.sin_port));
            continue;
        }

        for(auto &client : clients)
        {
            int client_sock = client.first;
            printf("sock #%d\n", client_sock);

            if(!FD_ISSET(client_sock, &read_sds)) continue;

            int bytes_recv = recv(client_sock, buf, BUFSIZ, 0);
            printf("bytes_recv: %d\n", bytes_recv);

            //클라이언트가 프로그램을 강제로 종료하여 클라이언트의 소켓은 닫혔는데 서버의 소켓은 열려있다면 recv가 무한하게 0 바이트를 받는다.
            bool conn_lost = bytes_recv <= 0 ? true : false;
            if(conn_lost)
            {
                printf("[Handler] Connection lost.\n");
                FD_CLR(client_sock, &read_sds);
                close(client_sock);
                clients.erase(client_sock);
                continue;
            }

            printf("%s", buf);
            std::map<std::string, std::string> headers = parseHeaders(buf);
            std::string method = headers["method"];
            std::string status = headers["status"];
            std::string id = headers["id"];
            int fin = std::stoi(headers["fin"]);

            if(fin == 1)
            {
                printf("[Handler] Connection closed.\n");
                FD_CLR(client_sock, &read_sds);
                close(client_sock);
                // TODO: segmentation fault
                // clients.erase(client_sock);
                continue;
            }
            if(method == "login")
            {
                if(authenticate(id))
                {
                    snprintf(buf, BUFSIZ, response_form.c_str(), "login", "success");
                    if(send(client_sock, buf, strlen(buf), 0) < 0)
                    {
                        printf("[Handler] Failed to send log-in msg.\n");
                    }
                    printf("[Handler] %s log-in.\n", id.c_str());

                    add_user(id, file_path);

                    continue;
                }

                snprintf(buf, BUFSIZ, response_form.c_str(), "login", "fail");
                if(send(client_sock, buf, strlen(buf), 0) < 0)
                {
                    printf("[Handler] Failed to send log-in msg.\n");
                }
                printf("[Handler] log-in failed: ID already in use.\n");
            }
            else if(method == "logout")
            {
                snprintf(buf, BUFSIZ, response_form.c_str(), "logout", "success");
                if(send(client_sock, buf, strlen(buf), 0) < 0)
                {
                    printf("[Handler] Failed to send log-out msg.\n");
                }
                printf("[Handler] %s: log-out.\n", id.c_str());
                remove_user(id, file_path);
                FD_CLR(client_sock, &read_sds);
                close(client_sock);
                clients.erase(client_sock);

                continue;
            }
            else if(method == "get")
            {
                snprintf(buf, BUFSIZ, response_form.c_str(), "get", "success");
            }
        }
    }
    return 0;
}