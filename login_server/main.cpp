#include "./login_server.h"

std::map<int, User> users;
std::vector<User> tmp_user;

const std::string file_path = "./user/online_users.txt";

int main(int argc, char *argv[])
{
    const int port = (argc > 1) ? std::atoi(argv[1]) : 10000;
    const int backlog = (argc > 2) ? std::atoi(argv[2]) : SOMAXCONN;
    
    int master_sock = server_socket();
    server_bind(master_sock, port);
    server_listen(master_sock, backlog);
    connection_handler(master_sock, file_path);
    close(master_sock);
}