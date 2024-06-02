#include "./login_server.h"

std::vector<User> tmp_user;
std::map<int, User> users;

const std::string db_path = "./user_db.txt";

int main(int argc, char *argv[])
{
    system("clear");
    
    const int port = (argc > 1) ? std::atoi(argv[1]) : 10000;
    const int backlog = (argc > 2) ? std::atoi(argv[2]) : SOMAXCONN;
    
    int server_sock = server_socket();
    server_bind(server_sock, port);
    server_listen(server_sock, backlog);
    conn_handler(server_sock, db_path);
    close(server_sock);
}