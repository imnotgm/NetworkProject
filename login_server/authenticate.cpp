#include "./login_server.h"

int authenticate(int sock_fd)
{
    char buf[BUFSIZ];
    int active, new_socket;
    int max_sd = sock_fd;

    fd_set read_sds;
    std::vector<int> client_sockets;
    FD_ZERO(&read_sds);
    FD_SET(sock_fd, &read_sds);
    // while(1)
    for(int i = 0; i < 5; i++)
    {
        printf("start while\n");
        FD_ZERO(&read_sds);
        FD_SET(sock_fd, &read_sds);
        for(int client_socket : client_sockets)
        {
            FD_SET(client_socket, &read_sds);
        }

        if((active = select(max_sd + 1, &read_sds, NULL, NULL, NULL)) < 0)
        {
            printf("[Authentication] Failed to select.\n");
            break;
        }

        if(FD_ISSET(sock_fd, &read_sds))
        {
            if((new_socket = server_accept(sock_fd)) < 0)
            {
                printf("[Authentication] Failed to accept from client\n");
                continue;
            }

            client_sockets.push_back(new_socket);
            FD_SET(new_socket, &read_sds);
            if(new_socket > max_sd)
                max_sd = new_socket;

            User tmp = user_tmp.back();
            printf("[Authentication] log-in attempt from socket #%d: (ip: %s, port: %d)\n",
                    new_socket, inet_ntoa(tmp.user_addr.sin_addr), ntohs(tmp.user_addr.sin_port));
            continue;
        }

        for(auto iter = client_sockets.begin(); iter != client_sockets.end(); )
        {
            int client_socket = *iter;

            if(FD_ISSET(client_socket, &read_sds))
            {
                if(recv(client_socket, buf, BUFSIZ, 0) <= 0)
                {
                    printf("[Authentication] Failed to receive login request msg or client disconnected.\n");
                    iter++;
                    continue;
                }

                std::map<std::string, std::string> headers = parseHeaders(buf);
                std::string id = headers["id"];
                int fin = std::stoi(headers["fin"]);

                if(fin == 1)
                {
                    printf("[Authentication] Exceeded max login attempt.\n");
                    close(client_socket);
                    iter = client_sockets.erase(iter);
                    continue;
                }

                if(id_check(id))
                {
                    snprintf(buf, BUFSIZ, response_form.c_str(), "login", "success");
                    if(send(client_socket, buf, strlen(buf), 0) < 0)
                    {
                        printf("[Authentication] Failed to send authentication msg.\n");
                    }
                    printf("[Authentication] log-in successful.\n");
                }
                else
                {
                    snprintf(buf, BUFSIZ, response_form.c_str(), "login", "fail");
                    if(send(client_socket, buf, strlen(buf), 0) < 0)
                    {
                        printf("[Authentication] Failed to send authentication msg.\n");
                    }
                    printf("[Authentication] log-in failed: ID already in use.\n");
                }
            }
            iter++;
        }
    }
    return 0;
}