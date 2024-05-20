#include "./login_server.h"

std::map<std::string, User> user_list;
std::vector<User> tmp_user;
std::string response_form =
    "method: %s\r\n"
    "authentication: %s\r\n"
    "\r\n";
    
int main(int argc, char *argv[])
{
    const int port = (argc > 1) ? std::atoi(argv[1]) : 10000;
    const int backlog = (argc > 2) ? std::atoi(argv[2]) : SOMAXCONN;
    
    int master_sock = server_socket();
    server_bind(master_sock, port);
    server_listen(master_sock, backlog);
    connection_handler(master_sock);
    close(master_sock);
}