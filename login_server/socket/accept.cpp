#include "./login_server.h"

int server_accept(int sock_fd)
{
    int user_sock;
    struct sockaddr_in user_addr;
    socklen_t addr_len = sizeof(user_addr);
    
    if((user_sock = accept(sock_fd, (struct sockaddr *) &user_addr, &addr_len)) < 0)
    {
        printf("Failed to accept.\n");
    }
    
    User user = {"tmp", sock_fd, user_addr};
    user_tmp.push_back(user);
    return user_sock;
}