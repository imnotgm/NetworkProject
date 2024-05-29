#include "./chat_server.h"

int conn_handler(int server_sock)
{
    char buf[BUFSIZ];
    int new_sock, max_fd = server_sock;
    fd_set read_sds;

    while(1)
    {
        printf("[conn_handler] log: While loop begins.\n");
        FD_ZERO(&read_sds);
        FD_SET(server_sock, &read_sds);
        memset(buf, 0, BUFSIZ);

        for(auto &user : users)
        {
            User client = user.second;
            int sock = client.sock;
            FD_SET(sock, &read_sds);
            if(max_fd < sock)
                max_fd = sock;
        }

        if((select(max_fd + 1, &read_sds, NULL, NULL, NULL)) < 0)
        {
            printf("[conn_handler] error: (select) No events on descriptors.\n");
            continue;
        }

        if(FD_ISSET(server_sock, &read_sds))
        {
            if((new_sock = server_accept(server_sock)) < 0)
            {
                printf("[conn_handler] error: (accept) Failed to accept client socket.\n");
                continue;
            }

            recv(new_sock, buf, BUFSIZ, 0);
            std::map<std::string, std::string> headers = parseHeaders(buf);
            std::string id = headers["id"];

            User new_user = tmp_user.back();
            new_user.id = id;
            users[id] = new_user;
            tmp_user.pop_back();

            printf("[conn_handler] Connection from '%s'(socket #%d, ip: %s, port: %d)\n",
                    id.c_str(), new_sock, inet_ntoa(new_user.addr.sin_addr), ntohs(new_user.addr.sin_port));

            continue;
        }

        std::vector<std::string> closed_clients;

        for(auto &user : users)
        {
            memset(buf, 0, BUFSIZ);
            auto &client = user.second;

            if(!FD_ISSET(client.sock, &read_sds)) continue;

            int bytes_recv = recv(client.sock, buf, BUFSIZ, 0);
            printf("[conn_handler] request msg from user '%s'(sock #%d): %dB received.\n", client.id.c_str(), client.sock, bytes_recv);

            //클라이언트가 프로그램을 강제로 종료하여 클라이언트의 소켓은 닫혔는데 서버의 소켓은 열려있다면 recv가 무한하게 0 바이트를 받는다.
            bool conn_lost = (bytes_recv <= 0) ? true : false;
            if(conn_lost)
            {
                printf("[conn_handler] error: Connection lost.\n");
                closed_clients.push_back(client.id);
                continue;
            }

            std::map<std::string, std::string> headers = parseHeaders(buf);
            std::string request_line = headers["method"];
            std::vector<std::string> method = split(request_line, " ");
            std::string id = headers["id"];
            std::string name = headers["session"];
            std::string request_body = headers["body"];

            // std::string resoponse_form =    "status: %s\r\n"
            //                                 "type: %d\r\n"
            //                                 "content-length: %d\r\n"
            //                                 "\r\n"
            //                                 "%s";
            std::string status, type, response_body = "";

            if(method[0] == "GET")
            {
                if(method[1] == "/user")
                {
                    msg_handler(client, status = "OK", type = "msg", response_body = user_list(), request_line);
                }
                else if(method[1] == "/session")
                {
                    msg_handler(client, status = "OK", type = "msg", response_body = live_session_list(), request_line);
                }
                else
                    msg_handler(client, status = "Bad", type = "error", response_body = "wrong command", request_line);
            }
            else if(method[0] == "POST")
            {
                (*sessions[name]).broadcast("chat", id, request_body);
            }
            else if(method[0] == "SESSION")
            {
                if(method[1] == "/new")
                {
                    if(sessions.find(name) == sessions.end())
                    {
                        client.session = name;
                        sessions[name] = new Session(name, id, client);
                        msg_handler(client, status = "OK", type = "msg", response_body = "# New session created #", request_line);
                    }
                    else
                        msg_handler(client, status = "Bad", type = "error", response_body = "Session already exists.", request_line);
                }
                else if(method[1] == "/join")
                {
                    if(sessions.find(name) == sessions.end())
                    {
                        printf("[conn_handler] Failed to find session '%s'.\n", name.c_str());
                        msg_handler(client, status = "Bad", type = "error", response_body = "No such session.", request_line);
                    }
                    else if((*sessions[name]).join(id, client))
                    {
                        client.session = name;
                        client.is_available = 0;
                        (*sessions[name]).broadcast("info", id, "joined the session.");
                        msg_handler(client, status = "OK", type = "msg", response_body = "# Joined the session #", request_line);
                    }
                    else
                        msg_handler(client, status = "Bad", type = "error", response_body = "You have already joined.", request_line);
                }
                else if(method[1] == "/leave")
                {
                    if(sessions.find(name) == sessions.end())
                    {
                        printf("[conn_handler] Failed to find session '%s'.\n", name.c_str());
                        msg_handler(client, status = "Bad", type = "error", response_body = "No such session.", request_line);
                    }
                    else if((*sessions[name]).leave(id))
                    {
                        client.session = "";
                        client.is_available = 1;
                        (*sessions[name]).broadcast("info", id, "leaved the session.");
                        msg_handler(client, status = "OK", type = "msg", "Succeeded to leave the session.", request_line);
                    }
                    else
                        msg_handler(client, status = "Bad", type = "error", "You are not in this session.", request_line);
                }
            }
            else
            {
                status = "Bad";
                msg_handler(users[id], status, "error", "", request_line);
            }
        }
        for(auto id : closed_clients)
        {
            int sock = users[id].sock;
            FD_CLR(sock, &read_sds);
            close(sock);
            users.erase(id);

            printf("[conn_handler] Session closed for user '%s'.\n", id.c_str());
        }
        for(auto session : sessions)
        {
            std::string name = session.first;
            if((*session.second).empty())
            {
                delete session.second;
                sessions.erase(name);
                printf("[conn_handler] Chat session '%s' closed.", name.c_str());
            }
        }
    }
    return 0;
}