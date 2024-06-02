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
            std::string request = headers["request"];
            std::vector<std::string> request_line = split(request, " ");
            std::string method = request_line[0], target = request_line[1];
            std::string id = headers["id"];
            std::string session_id = headers["session"];
            std::string request_body = headers["body"];

            // std::string resoponse_form =
            //             "status_code: %s\r\n"
            //             "sender: %s\r\n"
            //             "content-type: %d\r\n"
            //             "content-length: %d\r\n"
            //             "\r\n"
            //             "%s";
            std::string status_code, sender = "system", content_type = "", response_body = "";

            char tmp_buf[BUFSIZ];
            memset(tmp_buf, 0, BUFSIZ);

            if(method == "GET")
            {
                if(target == "/user")
                {
                    status_code = "OK";
                    content_type = "msg";
                    response_body = user_list(id);
                }
                else if(target == "/chat")
                {
                    status_code = "OK";
                    content_type = "msg";
                    response_body = live_chat_list();
                }
                else
                {
                    status_code = "Bad Request";
                    content_type = "error";
                    response_body = "Wrong argument for command 'ls'";
                }
            }
            else if(method == "CHAT")
            {
                if(target == "/broadcast")
                {
                    (*chat_groups[session_id]).broadcast("chat", id, request_body);
                }
                else if(target == "/new")
                {
                    if(chat_groups.find(session_id) == chat_groups.end())
                    {
                        client.session = session_id;
                        client.is_available = 0;
                        chat_groups[session_id] = new ChatGroup(session_id, id, client);
                        std::vector<std::string> members = split(request_body, " ", 0);
                        for(auto &mem_id : members)
                        {
                            std::cout << mem_id << std::endl;
                            if(users.find(mem_id) == users.end() || (*chat_groups[session_id]).isMember(mem_id))
                                continue;

                            msg_handler(users[mem_id], request, status_code = "New Session", sender = id,content_type = "ask", response_body = session_id);
                        }

                        status_code = "New Session";
                        content_type = "msg";
                        snprintf(tmp_buf, BUFSIZ, "\"New chat session '%s' started\"", session_id.c_str());
                        response_body = tmp_buf;
                    }
                    else
                    {
                        status_code = "Bad Request";
                        content_type = "error";
                        response_body = "Duplicate chat name";
                    }
                }
                else if(target == "/join")
                {
                    if(!client.session.empty())
                    {
                        status_code = "Bad Request";
                        content_type = "error";
                        response_body = "You must leave current chat to join anther one";
                    }
                    if(chat_groups.find(session_id) == chat_groups.end())
                    {
                        printf("[conn_handler] Failed to find chat '%s'.\n", session_id.c_str());
                        status_code = "Bad Request";
                        content_type = "error";
                        response_body = "No such chat";
                    }
                    else if((*chat_groups[session_id]).join(id, client))
                    {
                        client.session = session_id;
                        client.is_available = 0;

                        snprintf(tmp_buf, BUFSIZ, "'%s' joined the chat.", id.c_str());
                        response_body = tmp_buf;
                        (*chat_groups[session_id]).broadcast("info", id, response_body);

                        status_code = "New Session";
                        content_type = "msg";
                        response_body = "\"You've joined the chat.\"";
                    }
                    else
                    {
                        status_code = "Bad Request";
                        content_type = "error";
                        response_body = "You have already joined.";
                    }
                }
                else if(target == "/leave")
                {
                    if(chat_groups.find(session_id) == chat_groups.end())
                    {
                        status_code = "Bad Request";
                        content_type = "error";
                        response_body = "No such chat.";
                        
                        printf("[conn_handler] Failed to find chat '%s'.\n", session_id.c_str());
                    }
                    else if((*chat_groups[session_id]).leave(id))
                    {
                        client.session = "";
                        client.is_available = 1;

                        snprintf(tmp_buf, BUFSIZ, "'%s' leaved the chat.", id.c_str());
                        response_body = tmp_buf;
                        (*chat_groups[session_id]).broadcast("info", "system", response_body);

                        status_code = "OK";
                        content_type = "msg";
                        response_body = "Succeeded to leave the chat.";
                    }
                    else
                    {
                        status_code = "Bad Request";
                        content_type = "error";
                        response_body = "You are not in this chat.";
                    }
                }
            }
            else
            {
                status_code = "Bad Request";
                content_type = "error";
                response_body = "Not viable request";
            }
            msg_handler(users[id], request, status_code, sender, content_type, response_body);
        }
        for(auto id : closed_clients)
        {
            std::string session_id = users[id].session;
            if(chat_groups.find(session_id) != chat_groups.end())
            {
                (*chat_groups[session_id]).leave(id);
                (*chat_groups[session_id]).broadcast("system", id, "leaved the chat.");
                printf("[conn_handler] User '%s' was forcibly removed from the group '%s' due to a disconnection.\n", id.c_str(), session_id.c_str());
            }
            
            int sock = users[id].sock;
            FD_CLR(sock, &read_sds);
            close(sock);
            users.erase(id);

            printf("[conn_handler] Connection closed for user '%s'.\n", id.c_str());
        }
        // for(auto &groups : chat_groups) map 순회 과정에서 erase 이후 segmentation fault.
        for(auto it = chat_groups.begin(); it != chat_groups.end();)
        {
            ChatGroup *group_obj = it->second;
            std::string session_id = it->first;
            if(group_obj->empty())
            {
                // erase 함수로 다음 유효한 반복자를 반환.
                it = chat_groups.erase(it);
                delete group_obj;
                printf("[conn_handler] Not used chat '%s' closed.\n", session_id.c_str());
            }
            else
            {
                it++;
            }
        }
    }
    return 0;
}