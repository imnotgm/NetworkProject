#include "../login_server.h"

int server_accept(int sock)
{
    int user_sock;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    
    if((user_sock = accept(sock, (struct sockaddr *) &addr, &addr_len)) < 0)
    {
        printf("Failed to accept.\n");
    }
    
    User user = {"tmp", "", 0,user_sock, addr};
    tmp_user.push_back(user);

    return user_sock;
}