#include "./login_server.h"

int conn_handler(int master_sock, const std::string& file_path)
{
    char buf[BUFSIZ];
    int new_socket, max_fd = master_sock;

    fd_set read_sds;

    while(1)
    {
        printf("===================================================\n");
        FD_ZERO(&read_sds);
        FD_SET(master_sock, &read_sds);
        memset(buf, 0, BUFSIZ);

        for(auto &user : users)
        {
            FD_SET(user.first, &read_sds);
        }

        if((select(max_fd + 1, &read_sds, NULL, NULL, NULL)) < 0)
        {
            printf("[Handler/select] No events on descriptors.\n");
            continue;
        }

        if(FD_ISSET(master_sock, &read_sds))
        {
            if((new_socket = server_accept(master_sock)) < 0)
            {
                printf("[Handler/accept] Failed to accept.\n");
                continue;
            }

            FD_SET(new_socket, &read_sds);
            if(new_socket > max_fd)
                max_fd = new_socket;

            User new_user = tmp_user.back();
            users[new_socket] = new_user;
            printf("[Handler] Connection from socket #%d: (ip: %s, port: %d)\n",
                    new_socket, inet_ntoa(new_user.addr.sin_addr), ntohs(new_user.addr.sin_port));
            continue;
        }

        std::vector<int> closed_socks;

        for(auto &user : users)
        {
            memset(buf, 0, BUFSIZ);
            int sock = user.first;

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

            std::string body = "";
            std::string detail = "";

            if(fin == 1)
            {
                printf("[Handler] Connection closed.\n");
                closed_socks.push_back(sock);
                continue;
            }
            if(method == "LOG_IN")
            {
                if(authenticate(id, file_path))
                {
                    add_user(sock, id, file_path);
                    body = online_users();
                    msg_handler(sock, buf, BUFSIZ, 1, body, method, detail);

                    continue;
                }
                detail = "ID already in uses";
                msg_handler(sock, buf, BUFSIZ, 0, body, method, detail);
            }
            else if(method == "LOG_OUT")
            {
                msg_handler(sock, buf, BUFSIZ, 1, body, method, detail);
                closed_socks.push_back(sock);

                continue;
            }
            else if(method == "GET")
            {
                body = online_users();
                msg_handler(sock, buf, BUFSIZ, 1, body, method, detail);
            }
        }
        for(int sock : closed_socks)
        {
            std::string id = users[sock].id;
            printf("[Handler] closing session for USER %s\n", id.c_str());

            remove_user(sock, file_path);
            FD_CLR(sock, &read_sds);
            close(sock);
            users.erase(sock);
        }
    }
    return 0;
}