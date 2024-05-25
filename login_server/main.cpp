#include "./login_server.h"

std::vector<User> tmp_user;
std::map<int, User> users;

const std::string db_path = "./user/user_db.txt";

int main(int argc, char *argv[])
{
    const int port = (argc > 1) ? std::atoi(argv[1]) : 10000;
    const int backlog = (argc > 2) ? std::atoi(argv[2]) : SOMAXCONN;
    
    int master_sock = server_socket();
    server_bind(master_sock, port);
    server_listen(master_sock, backlog);
    conn_handler(master_sock, db_path);
    close(master_sock);
}