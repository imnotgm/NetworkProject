#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <iostream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <string>
#include <map>
#include "./user.h"

std::map<std::string, User> user_list;

int server_socket();
void server_bind(int sock_fd, int port);
void server_listen(int sock_fd, int backlog);
int server_accept(int sock_fd);



